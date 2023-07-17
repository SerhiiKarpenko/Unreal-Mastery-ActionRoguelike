// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams objectParameters;
	objectParameters.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* player = GetOwner(); // get's the owner of component
	
	FVector eyeLocation;
	FRotator eyeRotation;

	player->GetActorEyesViewPoint(eyeLocation, eyeRotation);

	FVector end = eyeLocation + (eyeRotation.Vector() * 1000);
	
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(hit, eyeLocation, end, objectParameters); //RAY TRACING;

	AActor* hitActor = hit.GetActor();
	
	if(hitActor == nullptr)
		return;
	
	
	if(!hitActor->Implements<USGameplayInterface>())
		return;
		
	APawn* playerPawn = Cast<APawn>(player);
	ISGameplayInterface::Execute_Interact(hitActor, playerPawn);
}

