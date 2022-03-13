// Made by Jan Puto 2022 :D

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blackhole.generated.h"

UCLASS()
class TPROGUELIKE_API ABlackhole : public AActor
{
	GENERATED_BODY()
	
public:	

	ABlackhole();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* DestructionSphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* CollisionSphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* BlackholeParticleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class URadialForceComponent* RadialForceComp;
	

	virtual void BeginPlay() override;

	UFUNCTION()
	void StartSucking(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
