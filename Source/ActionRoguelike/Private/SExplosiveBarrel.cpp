// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"


ASExplosiveBarrel::ASExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	StaticMesh->SetupAttachment(RootComponent);

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("Radial Force Component");
	RadialForceComponent->SetupAttachment(StaticMesh);

}

void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

