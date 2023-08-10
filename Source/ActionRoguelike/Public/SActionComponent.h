#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SAction.h"
#include "SActionEffect.h"
#include "Components/ActorComponent.h"
#include "SActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USActionComponent();

	// player states like, SPRINTING, ATTACKING, STUNNED, other components now can read from this container, and check the player state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<USAction*> Actions;
	
	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<USAction>> DefaultActions;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// __________________________________________________________________________//

	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void AddAction(AActor* instigator, TSubclassOf<USAction> actionClass);
	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void RemoveAction(USAction* UsActionEffect);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StartActionByName(AActor* instigator, FName actionName);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StopActionByName(AActor* instigator, FName actionName);
};
