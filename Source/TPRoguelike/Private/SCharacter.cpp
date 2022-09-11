 // Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SAttributeComponent.h"
#include "SProjectileBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////
//////	Setups
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComponent"));

	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComponent"));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	PrimaryWeaponSocketName = TEXT("RightHandSocket");
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}


//////////////////////////////////////////////////////
//////	BeginPlay + Tick
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}


//////////////////////////////////////////////////////
//////	Health + Death
void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,
	float DeltaHealth)
{
	if (NewHealth <= 0.f && DeltaHealth < 0.0f)	// "DeltaHealth" checks if we ware damaged of healed
	{
		OnDeath();
	}
}

void ASCharacter::OnDeath()
{
	TObjectPtr<APlayerController> PlayerControler = Cast<APlayerController>(Controller);
	DisableInput(PlayerControler);

	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


//////////////////////////////////////////////////////
//////	Movement + interactions
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Q_Ability", IE_Pressed, this, &ASCharacter::Q_Ability);
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;
	
	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, Value);
}

void ASCharacter::Jump()
{
	ACharacter::Jump();
}


//////////////////////////////////////////////////////
//////	Abilities
void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(PrimaryAttackAnim);

	// Delay before s
	GetWorldTimerManager().SetTimer(TH_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.15f);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	if(ensureMsgf(PrimaryAttack_ProjectileClass, TEXT("PrimaryAttack_ProjectileClass is missing! Please saaign PrimaryAttack_ProjectileClass in your Character")))
	{
		//AController* Controller = GetController();
		
		FVector TraceStart = FVector::ZeroVector;
		FRotator EyeRotation;
		Controller->GetPlayerViewPoint(TraceStart, EyeRotation);
		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = TraceStart + ShotDirection * 5000;

		FHitResult HitResult;
		bool bHitSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WorldStatic);
		
		if(bHitSuccess)
		{
			TraceEnd = HitResult.ImpactPoint;
		}

		FVector HandLocation = GetMesh()->GetSocketLocation(PrimaryWeaponSocketName);
		FRotator ProjectileSpawnRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, TraceEnd);
		
		// SpawnTM == SpawnTransformMatrix
		FTransform SpawnTM = FTransform(ProjectileSpawnRotation, HandLocation);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
	
		ASProjectileBase* ProjectileSpawned = GetWorld()->SpawnActor<ASProjectileBase>(PrimaryAttack_ProjectileClass, SpawnTM, SpawnParams);
		GetCapsuleComponent()->IgnoreActorWhenMoving(ProjectileSpawned, true);

		// Spawn FX
		UGameplayStatics::SpawnEmitterAttached(ProjectileSpawned->SpawnVFX, GetMesh(), PrimaryWeaponSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		DrawDebugSphere(GetWorld(), SpawnTM.GetLocation(), 3.f, 8, FColor::Purple, false, 2.f);
		DrawDebugSphere(GetWorld(), TraceEnd, 3.f, 8, FColor::Blue, true, 2.f);
	}
}

void ASCharacter::Q_Ability()
{
	PlayAnimMontage(Q_AbilityAnim);

	GetWorldTimerManager().SetTimer(TH_Q_Ability, this, &ASCharacter::Q_Ability_TimeElapsed, 0.15f);
}

void ASCharacter::Q_Ability_TimeElapsed()
{
	FTransform SpawnTM = FTransform(GetControlRotation(), GetMesh()->GetSocketLocation(PrimaryWeaponSocketName));

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(Q_Ability_ProjectileClass, SpawnTM, SpawnParams);
	DrawDebugSphere(GetWorld(), SpawnTM.GetLocation(), 8.f, 8, FColor::Purple, false, 2.f);
}

void ASCharacter::PrimaryInteract()
{
	InteractionComponent->PrimaryInteract();
}
