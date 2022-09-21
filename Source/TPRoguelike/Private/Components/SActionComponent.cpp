// Made by Jan Puto 2022 :D


#include "Components/SActionComponent.h"
#include "Actions/SAction.h"

USActionComponent::USActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<USAction> DefaultActionClass : DefaultActions)
	{
		AddAction(DefaultActionClass);
	}
}

void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void USActionComponent::AddAction(TSubclassOf<USAction> ActionClass)
{
	if (!ensureAlways(ActionClass))
	{
		return;
	}

	TObjectPtr<USAction> NewAction = NewObject<USAction>(this, ActionClass);
	if (NewAction)
	{
		Actions.Add(NewAction);
	}
}


bool USActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (TObjectPtr<USAction> Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->StartAction(Instigator);
			return true;
		}
	}

	return false;
}

bool USActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (TObjectPtr<USAction> Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->StopAction(Instigator);
			return true;
		}
	}

	return false;
}
