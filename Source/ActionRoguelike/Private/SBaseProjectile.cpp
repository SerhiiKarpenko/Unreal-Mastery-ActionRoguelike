

#include "SBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASBaseProjectile::ASBaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	ProjectileSphereComponent->SetCollisionProfileName("Projectile");
	
	RootComponent = ProjectileSphereComponent;
	
	ProjectileParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("Projectile Particle System Component");
	ProjectileParticleSystemComponent->SetupAttachment(ProjectileSphereComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
}

void ASBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBaseProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
}

void ASBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASBaseProjectile::DestroyOnCollision_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystemToCreateOnDestroy, GetActorLocation(), GetActorRotation());
	Destroy();
}


