// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

ASExplosiveBarrel::ASExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = StaticMeshComponent;
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("Radial Force Component");
	RadialForceComponent->SetupAttachment(StaticMeshComponent);

	RadialForceComponent->Radius = 700;
	RadialForceComponent->ForceStrength = 300000.0f;
	RadialForceComponent->ImpulseStrength = 300000.0f;
	
	RadialForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void ASExplosiveBarrel::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();
}

void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnHit);
}

void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

