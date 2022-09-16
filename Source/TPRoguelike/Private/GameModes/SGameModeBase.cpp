// Made by Jan Puto 2022 :D


#include "GameModes/SGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "AI/SAICharacter.h"
#include "SAttributeComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"


ASGameModeBase::ASGameModeBase()
{

}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (bCanSpawnBots)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_SpawnBot, this, &ASGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
	}
}

void ASGameModeBase::SpawnBotTimerElapsed()
{
	// RandomBest5Pct mean that as a result we will get SINGLE random locatoin from bast 5 percent results
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryCompleted);
	}
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawn Bot EQS failed!"));
		return;
	}

	int32 NrOfAliveBots = 0;
	for (TActorIterator<ASAICharacter> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		TObjectPtr<ASAICharacter> Bot = *Iterator;

		TObjectPtr<USAttributeComponent> AttribComp = Cast<USAttributeComponent>(Bot->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(ensure(AttribComp) && AttribComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	if (ensureMsgf(DifficultyCurve, TEXT("DifficultyCurve is missing! Please assign DifficultyCurve in your Game Mode")))
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
		UE_LOG(LogTemp, Warning, TEXT("Bots on map: %i, Bots limit: %i"), NrOfAliveBots, MaxBotCount);
	}

	// Checks if we can spawn more bots based on the amount of them in the level
	if (NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("Max amount of bots on map. Skipping bot spawn"));
		return;
	}
	
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
		DrawDebugSphere(GetWorld(), Locations[0], 20, 20, FColor::Blue, false, 20.f);
	}
}
