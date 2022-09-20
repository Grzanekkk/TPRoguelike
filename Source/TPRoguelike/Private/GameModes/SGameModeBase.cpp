// Made by Jan Puto 2022 :D


#include "GameModes/SGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "AI/SAICharacter.h"
#include "SCharacter.h"
#include "SAttributeComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("jp.SpawnBots"), true, TEXT("Enable spawning of bots via timer."), ECVF_Cheat);


ASGameModeBase::ASGameModeBase()
{

}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBot, this, &ASGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ASGameModeBase::SpawnBotTimerElapsed()
{
	if (!bCanSpawnBots)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning bots disabled via bCanSpawnBots in GameMode"));
		return;
	}

	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning bots disabled via CVarSpawnBots command"));
		return;
	}

	// Basicly GetAllActorsOfClass
	int32 NrOfAliveBots = 0;
	for (TActorIterator<ASAICharacter> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		TObjectPtr<ASAICharacter> Bot = *Iterator;

		if (USAttributeComponent::IsActorAlive(Bot))
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
	
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
		DrawDebugSphere(GetWorld(), Locations[0], 20, 20, FColor::Blue, false, 20.f);
	}
}

void ASGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	TObjectPtr<ASCharacter> Player = Cast<ASCharacter>(VictimActor);
	if (Player)
	{
		// Its here and not in header file because we do not want to reuse this timer wher respawning two players at the same time
		FTimerHandle RespawnDelay_TimerHandle;
		FTimerDelegate RespawnPlayer_Delegate;

		RespawnPlayer_Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());

		GetWorldTimerManager().SetTimer(RespawnDelay_TimerHandle, RespawnPlayer_Delegate, PlayerRespawnDelay, false);
	}

	UE_LOG(LogTemp, Warning, TEXT("OnActorKilled: Victim: %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(VictimActor));
}

void ASGameModeBase::RespawnPlayerElapsed(AController* PlayerController)
{
	UE_LOG(LogTemp, Warning, TEXT("Respawning Player"));

	PlayerController->UnPossess();
	RestartPlayer(PlayerController);
}


////////////////////////////////////////////////////
/// Cheats
void ASGameModeBase::KillAllAI()
{
	for (TActorIterator<ASAICharacter> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		TObjectPtr<ASAICharacter> Bot = *Iterator;

		USAttributeComponent::GetAttributeComponent(Bot)->Kill(Bot);
	}
}