
#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "Components/ActorComponent.h"
#include "SActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USActionComponent();

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
	void AddAction(TSubclassOf<USAction> actionClass);
		
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StartActionByName(AActor* instigator, FName actionName);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StopActionByName(AActor* instigator, FName actionName);
};
