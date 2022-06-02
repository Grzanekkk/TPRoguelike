// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "SPotionBase.h"
#include "SHealingPotion.generated.h"

UCLASS()
class TPROGUELIKE_API ASHealingPotion : public ASPotionBase
{
	GENERATED_BODY()
	
public:
	ASHealingPotion();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	UPROPERTY(EditDefaultsOnly, Category = "Healing")
	float HealingAmount = 50;

protected:
	virtual void BeginPlay() override;

	virtual void UsePotion(APawn* InstigatorPawn) override;
};
