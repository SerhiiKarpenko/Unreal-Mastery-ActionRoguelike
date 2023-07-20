// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

ASTeleportProjectile::ASTeleportProjectile()
{
	particlesToActivateOnStopOrDestroy = CreateDefaultSubobject<UParticleSystemComponent>("Particles System Component To Create On End");
	particlesToActivateOnStopOrDestroy->SetupAttachment(ProjectileSphereComponent);
	
	particlesToActivateOnStart = CreateDefaultSubobject<UParticleSystemComponent>("Particles System Component To Create Start");
	particlesToActivateOnStart->SetupAttachment(ProjectileSphereComponent);
	
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DestroyHandle, this, &ASTeleportProjectile::StopProjectile, 0.2f);
}

void ASTeleportProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ProjectileSphereComponent->OnComponentHit.AddDynamic(this, &ASTeleportProjectile::TeleportImmediately);
}

void ASTeleportProjectile::StopMovement()
{
	ProjectileMovementComponent->StopMovementImmediately();
}

void ASTeleportProjectile::StopProjectile()
{
	StopMovement();
	SpawnExplosionParticles();
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ASTeleportProjectile::TeleportPlayerToEndPosition, 0.2f);
}

void ASTeleportProjectile::TeleportPlayerToEndPosition()
{
	GetInstigator()->TeleportTo(GetActorLocation(), GetInstigator()->GetActorRotation(), true, true);
	Destroy();
}

void ASTeleportProjectile::TeleportImmediately(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(DestroyHandle);
	GetWorldTimerManager().ClearTimer(TeleportHandle);
	SpawnExplosionParticles();
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ASTeleportProjectile::TeleportPlayerToEndPosition, 0.2f);
}

void ASTeleportProjectile::SpawnExplosionParticles()
{
	particlesToActivateOnStopOrDestroy->Activate();
}




