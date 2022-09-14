// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"


class UEnvQuery;

UCLASS()
class TPROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UEnvQuery> SpawnBotQuery;

	UPROPERTY()
	FTimerHandle TimerHandle_SpawnBot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	float SpawnTimerInterval = 2.f;

	void SpawnBotTimerElapsed();

public:
	ASGameModeBase();

	virtual void StartPlay() override;

};
