// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class TPROGUELIKE_API ASMagicProjectile : public ASProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage;
	
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	
	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
	//virtual void Explode_Implementation() override;
};
