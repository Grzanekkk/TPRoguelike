// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor,  class USAttributeComponent*, OwningComp, float, NewHealth, float, HealthDelta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static TObjectPtr<USAttributeComponent> GetAttributeComponent(AActor* FromActor);

	// Returns false is Actor doesn`t have AttributeComponent
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static bool IsActorAlive(AActor* Actor);

	USAttributeComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth = 100.f;

	// HealthMax, Stamina, Mana, CritChance;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAlive() const; 

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsFullyHealed() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsHealthHigherThen(float IsHealthHigherThenThis) const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable,  Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float HealthDelta);
	
};
