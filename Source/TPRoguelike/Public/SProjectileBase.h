// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class USoundCue;


UCLASS(Abstract) // We cant spawn this actor + more... *
class TPROGUELIKE_API ASProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	ASProjectileBase();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAudioComponent> AudioComp;


	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
	void Explode();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;


	////////////////////////////////////////////////////
	/// Sounds
	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	TObjectPtr<USoundCue> FlightSound;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	TObjectPtr<USoundCue> ImpactSound;
};
