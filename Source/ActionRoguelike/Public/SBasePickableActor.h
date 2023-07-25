#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "SPickableInterface.h"
#include "GameFramework/Actor.h"
#include "SBasePickableActor.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASBasePickableActor : public AActor, public ISGameplayInterface, public ISPickableInterface
{
	GENERATED_BODY()
	
public:	
	ASBasePickableActor();

protected:
	virtual void BeginPlay() override;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	virtual void Pickup_Implementation(APawn* InstigatorPawn) override;
	
};
