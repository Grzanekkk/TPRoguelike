// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"

UCLASS()
class TPROGUELIKE_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBarrel();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Radius;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* ParticleComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class URadialForceComponent* RadialForceComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* ExplosionRadiusSphere;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystem* ExplosionParticles;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void Explode();

	UFUNCTION(BlueprintImplementableEvent)
	void ExplodeBP();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
