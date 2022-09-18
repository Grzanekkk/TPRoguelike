// Made by Jan Puto 2022 :D

#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "AIController.h"
#include "SAttributeComponent.h"
#include "BrainComponent.h"
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

void ASAICharacter::Tick(float DeltaTime)
{
	if (bIsHealingOverTime)
	{
		TimeSinceLastHealing += DeltaTime;

		if (TimeSinceLastHealing >= HealingInterval)
		{
			Heal(HealthPerSecond);
			TimeSinceLastHealing = 0.f;
		}
	}
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);

	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChanged);
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
	
	DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.f, true);
}


bool ASAICharacter::SetTargetActor(AActor* TargetActor)
{
	// If we ware hit by another ai we will start shooting this ai (its kinda fun)
	if (TargetActor != this)
	{
		TObjectPtr<AAIController> AIController = Cast<AAIController>(GetController());
		if (AIController)
		{
			TObjectPtr<UBlackboardComponent> BBCComp = AIController->GetBlackboardComponent();

			BBCComp->SetValueAsObject("TargetActor", TargetActor);

			return true;
		}
	}

	return false;
}

////////////////////////////////////////////////////
/// Health + Death
void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float DeltaHealth)
{
	SetTargetActor(InstigatorActor);

	if (DeltaHealth < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->GetTimeSeconds());
	}

	if (DeltaHealth < 0 && !AttributeComponent->IsAlive())
	{
		OnDeath();
	}
}

void ASAICharacter::OnDeath()
{
	// Stoping Logic
	TObjectPtr<AAIController> AIController = Cast<AAIController>(GetController());
	if (ensure(AIController))
	{
		AIController->GetBrainComponent()->StopLogic("Killed");
	}

	// Set Ragdoll
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");


	if (bIsHealingOverTime)
	{
		StopHealingOverTime();
	}

	// Destroy Actor in 10s
	SetLifeSpan(10.f);
}

void ASAICharacter::Heal(float HealingAmount)
{
	// For now waiting is implemented in Behaviur Tree
	if (HealingAmount > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Healed for %f HP"), *this->GetName(), HealingAmount);
		AttributeComponent->ApplyHealthChange(this, HealingAmount);
	}
}

void ASAICharacter::StartHealingOverTime(float _HealthPerSecond, float _SecondsOfHealing)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Started Healing"), *this->GetName());

	SecondsOfHealing = _SecondsOfHealing;
	HealthPerSecond = _HealthPerSecond;
	bIsHealingOverTime = true;

	HealingParticleComp->Activate(true);

	// Heal a little at a start
	Heal(HealthPerSecond);
}

void ASAICharacter::StopHealingOverTime()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Stopped Healing"), *this->GetName());

	SecondsOfHealing = 0;
	HealthPerSecond = 0;
	bIsHealingOverTime = false;

	HealingParticleComp->Deactivate();
}
