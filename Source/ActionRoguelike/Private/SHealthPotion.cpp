#include "SHealthPotion.h"
#include "SAttributeComponent.h"


ASHealthPotion::ASHealthPotion()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	RootComponent = StaticMeshComponent;

	HealPower = 20.0f;
	CanBeUsed = true;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!CanBeUsed)
		return;
	
	Super::Interact_Implementation(InstigatorPawn);
	Pickup_Implementation(InstigatorPawn);
}

void ASHealthPotion::Pickup_Implementation(APawn* InstigatorPawn)
{
	Super::Pickup_Implementation(InstigatorPawn);
	USAttributeComponent* attributes = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (attributes == nullptr)
		return;
	
	if(!attributes->Heal(20.0f))
		return;

	CanBeUsed = false;
	StaticMeshComponent->SetVisibility(false);

	GetWorldTimerManager().SetTimer(RespawnHandle, this, &ASHealthPotion::Respawn_Implementation, 10);
}

void ASHealthPotion::Respawn_Implementation()
{
	ISRespawnableInterface::Respawn_Implementation();
	
	StaticMeshComponent->SetVisibility(true);
	CanBeUsed = true;
}

