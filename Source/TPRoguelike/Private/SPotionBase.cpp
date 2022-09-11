// Made by Jan Puto 2022 :D


#include "SPotionBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASPotionBase::ASPotionBase() 
{
	PrimaryActorTick.bCanEverTick = true;

	PotionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	RootComponent = PotionMesh;
}

void ASPotionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASPotionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASPotionBase::Interact_Implementation(APawn* InstigatorPawn)
{
	UsePotion(InstigatorPawn);
}

void ASPotionBase::UsePotion(APawn* InstigatorPawn)
{
	if (bCanBeInteracted)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickUpParticles, GetActorLocation());
		bCanBeInteracted = false;
		this->SetActorHiddenInGame(!bCanBeInteracted);

		GetWorldTimerManager().SetTimer(TH_InteractionDelay, this, &ASPotionBase::AllowInteraction, InteractionDelay);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot interact right now"));
	}
}

void ASPotionBase::AllowInteraction()
{
	bCanBeInteracted = true;
	this->SetActorHiddenInGame(!bCanBeInteracted);
}