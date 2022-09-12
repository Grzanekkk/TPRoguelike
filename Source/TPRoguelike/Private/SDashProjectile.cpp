// Made by Jan Puto 2022 :D

#include "SDashProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

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
	//Super::OnComponentHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	if (OtherActor == Cast<AActor>(GetInstigator()))
	{
		return;
	}


	GetWorldTimerManager().ClearTimer(ExpolsionTimer);

	Explode();
}

void ASDashProjectile::Explode()
{
	GetWorldTimerManager().SetTimer(TeleportationTimer, this, &ASDashProjectile::TeleportPlayer, TeleportDelay);

	UGameplayStatics::SpawnEmitterAtLocation(this, PlayerTeleportVFX, GetInstigator()->GetActorLocation(), GetInstigator()->GetActorRotation());

	MovementComp->StopMovementImmediately();
	ParticleComp->Deactivate();
}

void ASDashProjectile::TeleportPlayer()
{
	Super::Explode();

	TargetActor->TeleportTo(GetActorLocation(), TargetActor->GetActorRotation());

	Destroy();
}
