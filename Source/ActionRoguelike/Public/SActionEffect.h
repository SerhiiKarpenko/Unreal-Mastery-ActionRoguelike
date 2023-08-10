
#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SActionEffect.generated.h"

UCLASS()
class ACTIONROGUELIKE_API USActionEffect : public USAction
{
	GENERATED_BODY()


public:

	USActionEffect();
	
	void StartAction_Implementation(AActor* instigator) override;
	void StopAction_Implementation(AActor* instigator) override;

	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	float Duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	float Frequency;

	FTimerHandle FrequencyHandle;
	FTimerHandle DurationHandle;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Effect")
	void ExecuteEffect(AActor* instigator);
};
