// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPotionBase.generated.h"

UCLASS(Abstract)
class TPROGUELIKE_API ASPotionBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ASPotionBase();

	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InstigatorPawn);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void UsePotion(APawn* InstigatorPawn);

	UFUNCTION()
	void AllowInteraction();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> PotionMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Particles")
	TObjectPtr<UParticleSystem> PickUpParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionDelay = 10.f;

	UPROPERTY()
	FTimerHandle TH_InteractionDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	bool bCanBeInteracted = true;
};
