// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "SAttributeComponent.h"
#include "GameFramework/Actor.h"
#include "STargetDummy.generated.h"

UCLASS()
class TPROGUELIKE_API ASTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTargetDummy();

protected:
	UPROPERTY(VisibleAnywhere)
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float DeltaHealth);

};
