// Made by Jan Puto 2022 :D


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100;
}

bool USAttributeComponent::ApplyHealthChange(float HealthDelta)
{
	Health += HealthDelta;

	OnHealthChanged.Broadcast(nullptr, this, Health, HealthDelta);
	return true;
}
