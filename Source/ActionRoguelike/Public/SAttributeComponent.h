
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

// events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(
	FOnHealthChanged, // name of the delegate (event)
	AActor*, instigatorActor,
	USAttributeComponent* , owningComponent,
	float, newHealth,
	float, healthChange);  

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USAttributeComponent();

protected:

	// EditAnywhere - edit in BP editor pre-instance in level
	// VisibleAnywhere - 'read-only' in editor and level (Use for components)
	// EditDefaultsOnly - hide variable per-instance, edit in BP editor only
	// VisibleDefaultsOnly - 'read-only' access for variable, only in BP editor (uncommon)
	// EditInstanceOnly - allow only editing of instance (eg. when placed in level)
	// --
	//BlueprintReadOnly - read-only in the blueprint scripting (does not affect 'details' -panel)
	//BlueprintReadWrite = read-write access in blueprints
	// --
	// Category = "" - display only for detail panels anb blueprint context menu
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Attributes")
	float Health;

	//MaxHealth, Stamina, Strength

public:

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDie OnDie;
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyDamage(float damageToApply);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	void Die();

private:
	bool isAlive = true;
};
