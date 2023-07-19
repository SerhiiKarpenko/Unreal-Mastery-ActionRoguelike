// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "SExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditAnywhere, Category = "Particles to create on destroy")
	class UParticleSystem* ParticleSystem;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComponent;
	
public:	
	ASExplosiveBarrel();

protected:
	
	UFUNCTION() // if you want to bind method like the event, it must be marked as UFUNCTION
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
