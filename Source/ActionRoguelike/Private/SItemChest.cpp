// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"
#include "Components/StaticMeshComponent.h"

// Sets default values

ASItemChest::ASItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh Component");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("Lid Mesh Component");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitchOpen = 110;
	TargetPitchClose = 0;
	_isOpened = false;
}

// Called when the game starts or when spawned

void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame

void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASItemChest::OpenChest()
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitchOpen, 0, 0));
	_isOpened = true;
}

void ASItemChest::CloseChest()
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitchClose, 0, 0));
	_isOpened = false;
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	if(_isOpened)
		CloseChest();
	else
		OpenChest();
}

