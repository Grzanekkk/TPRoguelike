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
	UPROPERTY(EditDefaultsOnly, Category = "Effects|Particles")
	UParticleSystem* ImpactVFX;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Effects|Particles")
	UParticleSystem* SpawnVFX;	// Muzzle Flash

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAudioComponent> AudioComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Camera Shake")
	TSubclassOf<UCameraShakeBase> ImpactCameraShake;


	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual void Explode();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;


	////////////////////////////////////////////////////
	/// Sounds
	UPROPERTY(EditDefaultsOnly, Category = "Effects|Sounds")
	TObjectPtr<USoundCue> FlightSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Sounds")
	TObjectPtr<USoundCue> ImpactSound;
};
