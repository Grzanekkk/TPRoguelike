// Made by Jan Puto 2022 :D


#include "Pickups/SPickupBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASPickupBase::ASPickupBase() 
{
	PrimaryActorTick.bCanEverTick = true;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	RootComponent = MainMesh;
}

void ASPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASPickupBase::Interact_Implementation(APawn* InstigatorPawn)
{
	UsePickupItem(InstigatorPawn);
}

void ASPickupBase::UsePickupItem(APawn* InstigatorPawn)
{
	if (bCanBeInteracted)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickUpParticles, GetActorLocation());
		bCanBeInteracted = false;
		RootComponent->SetVisibility(bCanBeInteracted, true);

		GetWorldTimerManager().SetTimer(InteractionDelay_TimerHandle, this, &ASPickupBase::AllowInteraction, InteractionDelay);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot interact right now"));
	}
}

void ASPickupBase::AllowInteraction()
{
	bCanBeInteracted = true;
	RootComponent->SetVisibility(bCanBeInteracted, true);
}