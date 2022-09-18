// Made by Jan Puto 2022 :D


#include "AI/SBTTask_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TObjectPtr<AAIController> OwnerController = OwnerComp.GetAIOwner();
	if (ensure(OwnerController))
	{
		TObjectPtr<ACharacter> MyPawn = Cast<ACharacter>(OwnerController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		TObjectPtr<AActor> TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		if (USAttributeComponent::IsActorAlive(TargetActor))
		{
			return EBTNodeResult::Failed;
		}

		FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_Front");
		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = MyPawn;

		TObjectPtr<AActor> NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

		return NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}