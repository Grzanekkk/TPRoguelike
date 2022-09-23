// Made by Jan Puto 2022 :D


#include "Pickups/SHealingPotion.h"
#include "Components/SAttributeComponent.h"

ASHealingPotion::ASHealingPotion()
{

}

void ASHealingPotion::BeginPlay()
{
	Super::BeginPlay();
}

void ASHealingPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	UsePickupItem(InstigatorPawn);
}

void ASHealingPotion::UsePickupItem(APawn* InstigatorPawn)
{
	//Super::UsePotion(InstigatorPawn);

	if (bCanBeInteracted)
	{
		USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributeComponent(InstigatorPawn);
		if (AttributeComponent)
		{
			if (!AttributeComponent->IsFullyHealed())
			{
				AttributeComponent->ApplyHealthChange(this, HealingAmount);

				ASPickupBase::UsePickupItem(InstigatorPawn);
			}
		}
	}
}