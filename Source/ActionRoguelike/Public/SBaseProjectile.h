// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SBaseProjectile.generated.h"

UCLASS(ABSTRACT)
class ACTIONROGUELIKE_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBaseProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* ProjectileSphereComponent;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ProjectileParticleSystemComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ParticleSystemToCreateOnDestroy;

	UFUNCTION()
	virtual void OnActorHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit);

	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DestroyOnCollision();

	
};
