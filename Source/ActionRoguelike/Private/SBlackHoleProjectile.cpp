// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackHoleProjectile.h"
#include "Components/SphereComponent.h"
#include "SBaseProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASBlackHoleProjectile::ASBlackHoleProjectile()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("Radial Force Component");
	RadialForceComponent->SetupAttachment(ProjectileSphereComponent);
	
	RadialForceComponent->Radius = 1300;
	RadialForceComponent->ForceStrength = -900000.0f;
	RadialForceComponent->ImpulseStrength = 300000.0f;
	RadialForceComponent->RemoveObjectTypeToAffect(ObjectTypeQuery3);

	ProjectileSphereComponent->SetCollisionProfileName("BlackHole");
	ProjectileMovementComponent->InitialSpeed = 500.0f;

}


void ASBlackHoleProjectile::DestroyObjects(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	OtherActor->Destroy();
}

void ASBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASBlackHoleProjectile::DestroyObjects);
	OnDestroyed.AddDynamic(this, &ASBlackHoleProjectile::OnBlackHoleDestroy);
}

void ASBlackHoleProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASBlackHoleProjectile::OnBlackHoleDestroy(AActor* destoryedACtor)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ParticleSystem, GetActorLocation(), GetActorRotation());
	RadialForceComponent->FireImpulse();
}




