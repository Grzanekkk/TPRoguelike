// Made by Jan Puto 2022 :D

#include "SMagicProjectile.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SCharacter.h"
#include "Components/CapsuleComponent.h"
#include "FunctionLibrary/GameplayFunctionLibrary.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	Damage = 20.f;
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASMagicProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if(OtherActor && OtherActor != GetInstigator())
	//{
	//	UGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, Damage, Hit);
	//
	//	Super::Explode();
	//
	//	Destroy();
	//}
	//else
	//{
	//	return;
	//}
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, Damage, SweepResult);

		Super::Explode();

		Destroy();
	}
	else
	{
		return;
	}
}
