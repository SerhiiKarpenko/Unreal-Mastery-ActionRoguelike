// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "SBlackHoleProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASBlackHoleProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnBlackHoleDestroy(AActor* destoryedACtor);
	ASBlackHoleProjectile();
	
protected:

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* ParticleSystem;
	
	UPROPERTY(VisibleAnywhere)
	class URadialForceComponent* RadialForceComponent;

	class UStaticMeshComponent* StaticMeshComponent;
	FTimerHandle TimerToDestroy;
	FTimerHandle DestroyHandle;


	UFUNCTION()
	void DestroyObjects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
