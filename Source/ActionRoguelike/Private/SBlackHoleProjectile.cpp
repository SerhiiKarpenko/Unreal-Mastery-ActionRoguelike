// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SphereComponent.h"
#include "SBlackHoleProjectile.h"
#include "SBaseProjectile.h"

ASBlackHoleProjectile::ASBlackHoleProjectile()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("Radial Force Component");
	RadialForceComponent->SetupAttachment(ProjectileSphereComponent);
	
	RadialForceComponent->Radius = 700;
	RadialForceComponent->ForceStrength = 90000.0f;
	RadialForceComponent->RemoveObjectTypeToAffect(ObjectTypeQuery3);
}

void ASBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ASBlackHoleProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}




