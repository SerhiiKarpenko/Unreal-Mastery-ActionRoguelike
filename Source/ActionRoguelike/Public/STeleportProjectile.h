// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "STeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASTeleportProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

public:
	ASTeleportProjectile();

protected:
	void TeleportImmediately();
	
	void SpawnExplosionParticles();
	void TeleportPlayerToEndPosition();
	void StopProjectile();
	void DeactivateEffectComponent();
	void StopMovement();
	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
	
	FTimerHandle DestroyHandle;
	FTimerHandle TeleportHandle;
	
	/*UPROPERTY(EditAnywhere, Category = "Particles To Create On End")
	class UParticleSystem* particlesToSpawnOnStopOrDestroy;
	*/

	UPROPERTY(EditAnywhere, Category = "Particles To Create On End")
	class UParticleSystemComponent* particlesToActivateOnStopOrDestroy;
	
	UPROPERTY(EditAnywhere, Category = "Particles To Create On End")
	class UParticleSystemComponent* particlesToActivateOnStart;
};
