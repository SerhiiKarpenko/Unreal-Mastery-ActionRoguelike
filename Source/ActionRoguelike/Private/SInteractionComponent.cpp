// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"

USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_interactionDistance = 300;
}

void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams objectParameters;
	objectParameters.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* player = GetOwner(); // get's the owner of component
	
	FVector eyeLocation;
	FRotator eyeRotation;

	player->GetActorEyesViewPoint(eyeLocation, eyeRotation);

	_interactionDistance = 300;
	FVector end = eyeLocation + (eyeRotation.Vector() * _interactionDistance);
	
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(hit, eyeLocation, end, objectParameters); //RAY TRACING;

	AActor* hitActor = hit.GetActor();
	
	DrawDebugLine(GetWorld(), eyeLocation, end, FColor::Red, false, 2.0f, 0, 2.0f);
	
	if(hitActor == nullptr)
		return;
	
	
	if(!hitActor->Implements<USGameplayInterface>())
		return;
		
	APawn* playerPawn = Cast<APawn>(player);
	ISGameplayInterface::Execute_Interact(hitActor, playerPawn);
}

void USInteractionComponent::SecondInteract()
{
	FCollisionObjectQueryParams objectParameters;
	objectParameters.AddObjectTypesToQuery(ECC_WorldDynamic);
	FCollisionShape collisionShape;
	float radius = 30.0f;
	
	collisionShape.SetSphere(radius);

	AActor* player = GetOwner(); // get's the owner of component
	
	TArray<FHitResult> hits;
	
	FVector eyeLocation;
	FRotator eyeRotation;

	player->GetActorEyesViewPoint(eyeLocation, eyeRotation);
	
	FVector end = eyeLocation + (eyeRotation.Vector() * _interactionDistance);
	
	GetWorld()->SweepMultiByObjectType(
		hits,
		eyeLocation,
		end,
		FQuat::Identity,
		objectParameters,
		collisionShape);

	DrawDebugLine(GetWorld(), eyeLocation, end, FColor::Red, false, 2.0f, 0, 2.0f);
	
	for (FHitResult hit : hits)
	{
		AActor* hitActor = hit.GetActor();
		DrawDebugSphere(GetWorld(), hit.ImpactPoint, radius, 32, FColor::Red, false, 2.0f);
	
		if(hitActor == nullptr)
			continue;
		
		if(!hitActor->Implements<USGameplayInterface>())
			continue;
		
		// player will interact with first item detected.
		APawn* playerPawn = Cast<APawn>(player);
		ISGameplayInterface::Execute_Interact(hitActor, playerPawn);
		return; 
	}
}

