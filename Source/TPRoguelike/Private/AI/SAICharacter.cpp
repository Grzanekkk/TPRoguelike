// Made by Jan Puto 2022 :D

#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


ASAICharacter::ASAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComponent"));

	HealingParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HealingParticleComponent"));
	HealingParticleComp->SetupAttachment(RootComponent);
	HealingParticleComp->bAutoActivate = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);

	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChanged);
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	TObjectPtr<AAIController> AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		TObjectPtr<UBlackboardComponent> BBCComp = AIController->GetBlackboardComponent();

		BBCComp->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.f, true);
	}
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float DeltaHealth)
{

}

void ASAICharacter::OnDeath()
{

}


void ASAICharacter::Heal(float HealingAmount)
{
	if (HealingAmount > 0)
	{
		AttributeComponent->ApplyHealthChange(HealingAmount);

		HealingParticleComp->Activate(true);
	}
}
