// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

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
	RadialForceComponent->ForceStrength = 90000.0f;
	RadialForceComponent->ImpulseStrength = 90000.0f;
	
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
	UGameplayStatics::SpawnEmitterAtLocation(this, ParticleSystem, GetActorLocation(), GetActorRotation());
	
	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));
	
	/*
	 * %s - string
	 * %f - float
	 * logs: OtherActor: MyActor_1, at gametime: 124.4"
	 */
	
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	FString CombinedString = FString::Printf(TEXT("Hit was here: %s"), *Hit.ImpactPoint.ToString());

	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
	
	Destroy();
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

