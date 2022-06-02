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
		ASPotionBase::UsePotion(InstigatorPawn);

		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComponent)
		{
			AttributeComponent->ApplyHealthChange(HealingAmount);
		}
	}
}