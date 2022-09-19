// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "SGameModeBase.generated.h"


class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;

UCLASS()
class TPROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	bool bCanSpawnBots = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UEnvQuery> SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UCurveFloat>  DifficultyCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	float SpawnTimerInterval = 2.f;

	// It will use this value if we dont have DifficultyCurve assigned (we should assigne it thoe)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	int32 MaxBotCount = 10;

	UPROPERTY()
	FTimerHandle TimerHandle_SpawnBot;

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

public:
	ASGameModeBase();

	virtual void StartPlay() override;


protected:
	////////////////////////////////////////////////////
	/// Cheats

	UFUNCTION(Exec)
	void KillAllAI();
};
