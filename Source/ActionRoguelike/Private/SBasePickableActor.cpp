// Fill out your copyright notice in the Description page of Project Settings.


#include "SBasePickableActor.h"

// Sets default values
ASBasePickableActor::ASBasePickableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASBasePickableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASBasePickableActor::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);
}

void ASBasePickableActor::Pickup_Implementation(APawn* InstigatorPawn)
{
	ISPickableInterface::Pickup_Implementation(InstigatorPawn);
}




