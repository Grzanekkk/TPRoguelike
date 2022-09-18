// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class USAttributeComponent;
class UPawnSensingComponent;

UCLASS()
class TPROGUELIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASAICharacter();

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USAttributeComponent> AttributeComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPawnSensingComponent> PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UParticleSystemComponent> HealingParticleComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	////////////////////////////////////////////////////
	/// Health + Death
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float DeltaHealth);

	UFUNCTION()
	void OnDeath();

	UPROPERTY(VisibleAnywhere, Category = "Healing")
	bool bIsHealingOverTime = false;

	UPROPERTY(VisibleAnywhere, Category = "Healing")
	float HealingInterval = 1.f;

	UPROPERTY(VisibleAnywhere, Category = "Healing")
	float HealthPerSecond = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Healing")
	float SecondsOfHealing = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Healing")
	float TimeSinceLastHealing = 0.f;


public:
	UFUNCTION()
	void Heal(float HealingAmount);

	UFUNCTION()
	void StartHealingOverTime(float _HealthPerSecond, float _HealForSeconds);

	UFUNCTION()
	void StopHealingOverTime();


protected:
	virtual void PostInitializeComponents() override;
};
