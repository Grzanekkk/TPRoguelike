// Made by Jan Puto 2022 :D

#include "SMagicProjectile.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	Damage = 20.f;
}

// Called when the game starts or when spawned
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
	if(OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(AttributeComponent)
		{
			AttributeComponent->ApplyHealthChange(-Damage);
		}
		Super::Explode_Implementation();
	}
	else
	{
		return;
	}
}