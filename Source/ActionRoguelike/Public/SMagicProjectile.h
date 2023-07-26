// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystem;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	ASMagicProjectile();

protected:
	
	UFUNCTION()
	void OnOverlapWithActor(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep, const
		FHitResult& SweepResult
		);
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent; // collision component
	
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent; // we will give velocity to this component to move this forward
	
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComponent; // show something in the world

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere)
	class TSubclassOf<UCameraShakeBase> CameraShake;

public:	
	virtual void Tick(float DeltaTime) override;

};
