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

bool USAttributeComponent::ApplyHealthChange(float HealthDelta)
{
	Health += HealthDelta;

	Health = FMath::Clamp(Health, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(nullptr, this, Health, HealthDelta);
	return true;
}
