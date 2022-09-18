// Made by Jan Puto 2022 :D


#include "SHealingPotion.h"
#include "SAttributeComponent.h"

ASHealingPotion::ASHealingPotion()
{

}

void ASHealingPotion::BeginPlay()
{
	Super::BeginPlay();
}

void ASHealingPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	UsePotion(InstigatorPawn);
}

void ASHealingPotion::UsePotion(APawn* InstigatorPawn)
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

				ASPotionBase::UsePotion(InstigatorPawn);
			}
		}
	}
}