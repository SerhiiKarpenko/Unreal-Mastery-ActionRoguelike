#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

UCLASS(Blueprintable) // now we can create child classes from USAction 
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* instigator); // instigator = one who is responsible for  

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* instigator);
	
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;
	
};
