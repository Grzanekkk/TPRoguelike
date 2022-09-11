// Made by Jan Puto 2022 :D


#include "SDashProjectile.h"

ASDashProjectile::ASDashProjectile()
{

}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(ExpolsionTimer, this, &ASDashProjectile::Explode, ExplodeAfter);
}

void ASDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASDashProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(ExpolsionTimer);

	Explode();
}

void ASDashProjectile::Explode()
{
	Super::Explode();

	GetWorldTimerManager().SetTimer(TeleportationTimer, this, &ASDashProjectile::TeleportPlayer, TeleportDelay);
}

void ASDashProjectile::TeleportPlayer()
{
	TargetActor->TeleportTo(GetActorLocation(), TargetActor->GetActorRotation());

	Destroy();
}
