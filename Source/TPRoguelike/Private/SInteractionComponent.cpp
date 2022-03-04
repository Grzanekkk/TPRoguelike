// Made by Jan Puto 2022 :D


#include "SInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	AActor* Owner = GetOwner();

	FVector TraceStart = FVector::ZeroVector;
	FRotator EyeRotation;
	GetOwner()->GetActorEyesViewPoint(TraceStart, EyeRotation);

	FVector ShotDirection = EyeRotation.Vector();
	FVector TraceEnd = TraceStart + ShotDirection * 1000;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	//FHitResult Hit;
	//GetWorld()->LineTraceSingleByObjectType(Hit, TraceStart, TraceEnd, ObjectQueryParams);

	float Radius = 30.f;
	
	TArray<FHitResult> Hits;
	FCollisionShape SweepShape;
	SweepShape.SetSphere(Radius);
	
	bool bHitSuccess = GetWorld()->SweepMultiByObjectType(Hits, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, SweepShape);
	FColor LineColor = bHitSuccess ? FColor::Green : FColor::Red;

	for(FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{
			if(HitActor->Implements<USGameplayInterface>())
			{
				APawn* OwnerPawn = Cast<APawn>(Owner);
			
				ISGameplayInterface::Execute_Interact(HitActor, OwnerPawn);
				break;
			}
			DrawDebugSphere(GetWorld(), Hit.ImpactNormal, Radius, 32, LineColor, false, 2.f);
		}
	}
	
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, LineColor, false, 2, 0, 2);
}

