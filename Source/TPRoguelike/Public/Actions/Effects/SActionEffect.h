// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "Actions/SAction.h"
#include "SActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class TPROGUELIKE_API USActionEffect : public USAction
{
	GENERATED_BODY()

public:
	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category "Effect")
	float Duration = 0.0f;

	// Time between ticks to apply effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category "Effect")
	float Period = 0.f;

	FTimerHandle DurationTimerHandle;
	FTimerHandle PeriodTimerHandle;

	UFUNCTION(BlueprintNativeEvent, Category = "Effects")
	void ExecutePeriodicEffect(AActor* Instigator);
};
