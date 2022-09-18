// Made by Jan Puto 2022 :D


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = MaxHealth;
}

bool USAttributeComponent::IsAlive() const
{
	// returns true if alive, false if dead
	return Health > 0;
}

bool USAttributeComponent::IsFullyHealed() const
{
	return Health == MaxHealth;
}

bool USAttributeComponent::IsHealthHigherThen(float IsHealthHigherThenThis) const
{
	return Health > IsHealthHigherThenThis;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float HealthDelta)
{
	Health += HealthDelta;

	Health = FMath::Clamp(Health, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, HealthDelta);
	return true;
}

TObjectPtr<USAttributeComponent> USAttributeComponent::GetAttributeComponent(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	TObjectPtr<USAttributeComponent> AttributeCompont =	GetAttributeComponent(Actor);
	if (AttributeCompont)
	{
		return AttributeCompont->IsAlive();
	}

	return false;
}