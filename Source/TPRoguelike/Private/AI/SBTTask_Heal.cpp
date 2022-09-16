// Made by Jan Puto 2022 :D


#include "AI/SBTTask_Heal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/SAICharacter.h"

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TObjectPtr<ASAICharacter> AICharacter = Cast<ASAICharacter>(OwnerComp.GetOwner());
	if (ensure(AICharacter))
	{
		AICharacter->Heal(HealingAmount);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}