// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "SBlackHoleProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASBlackHoleProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

public:
	ASBlackHoleProjectile();
	
protected:
	
	UPROPERTY(VisibleAnywhere)
	class URadialForceComponent* RadialForceComponent;

	class UStaticMeshComponent* StaticMeshComponent;
	FTimerHandle TimerToDestroy;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
