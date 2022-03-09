// Made by Jan Puto 2022 :D


#include "ExplosiveBarrel.h"

#include "Chaos/ParticleIterator.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(RootComponent);
	ParticleComp->SetAutoActivate(false);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->Radius = 420.f;
	RadialForceComp->ForceStrength = 1200;
	
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	MeshComp->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnComponentHit);
}

void AExplosiveBarrel::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AExplosiveBarrel::Explode()
{
	RadialForceComp->FireImpulse();
	//ExplodeBP();
	ParticleComp->Activate(true);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticles, ParticleComp->GetComponentTransform());
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

