// Made by Jan Puto 2022 :D


#include "AI/SAIController.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
}