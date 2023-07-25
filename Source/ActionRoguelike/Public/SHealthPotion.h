#pragma once

#include "CoreMinimal.h"
#include "SBasePickableActor.h"
#include "SGameplayInterface.h"
#include "SPickableInterface.h"
#include "SRespawnableInterface.h"
#include "GameFramework/Actor.h"
#include "SHealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public ASBasePickableActor, public ISRespawnableInterface
{
	GENERATED_BODY()
	
public:	
	ASHealthPotion();

protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;

	float HealPower;
	bool CanBeUsed;
	FTimerHandle RespawnHandle;

public:
	void Pickup_Implementation(APawn* InstigatorPawn) override;
	void Interact_Implementation(APawn* InstigatorPawn) override;
	void Respawn_Implementation();
};
