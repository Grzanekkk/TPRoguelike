// Made by Jan Puto 2022 :D


#include "Blackhole.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABlackhole::ABlackhole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphareComp"));
	CollisionSphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionSphereComp->SetCollisionProfileName("Projectile");
	RootComponent = CollisionSphereComp;

	DestructionSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("DestructionComp"));

	ExplosionParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionParticleComp"));
	ExplosionParticleComp->SetupAttachment(CollisionSphereComp);

	FlyingParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FlyingParticleComp"));
	FlyingParticleComp->SetupAttachment(CollisionSphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->Radius = 420.f;
	RadialForceComp->ForceStrength = 1200;
	RadialForceComp->bIgnoreOwningActor = true;
}

// Called when the game starts or when spawned
void ABlackhole::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphereComp->OnComponentHit.AddDynamic(this, &ABlackhole::StartSucking);
	
}

// Called every frame
void ABlackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABlackhole::StartSucking(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	MovementComp->StopMovementImmediately();
	MovementComp->Activate(false);
	FlyingParticleComp->Activate(false);
	ExplosionParticleComp->Activate(true);

	//RadialForceComp->
}