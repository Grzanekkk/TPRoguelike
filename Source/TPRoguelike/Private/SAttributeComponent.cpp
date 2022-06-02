// Made by Jan Puto 2022 :D


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = MaxHealth;
}

bool USAttributeComponent::IsAlive() const
{
	if(Health > 0)
	{
		return true;
	}

	// Dead
	return false;
}

bool USAttributeComponent::ApplyHealthChange(float HealthDelta)
{
	Health += HealthDelta;

	//Health = FMath::Wrap(Health, 0.f, MaxHealth);
	Health = FMath::Clamp(Health, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(nullptr, this, Health, HealthDelta);
	return true;
}
