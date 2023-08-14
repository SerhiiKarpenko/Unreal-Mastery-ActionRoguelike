// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

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

	SetReplicates(true);
}


void ASItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASItemChest, _isOpened);
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
	UE_LOG(LogTemp, Log, TEXT("opening chest"));
	LidMesh->SetRelativeRotation(FRotator(TargetPitchOpen, 0, 0));
}

void ASItemChest::CloseChest()
{
	UE_LOG(LogTemp, Log, TEXT("closing chest"));
	LidMesh->SetRelativeRotation(FRotator(TargetPitchClose, 0, 0));
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	_isOpened = !_isOpened;
	OnRep_LidOpened();
}

void ASItemChest::OnRep_LidOpened()
{
	if(!_isOpened)
		CloseChest();
	else
		OpenChest();
}
