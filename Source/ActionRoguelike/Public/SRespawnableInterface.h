#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SRespawnableInterface.generated.h"

UINTERFACE(MinimalAPI)
class USRespawnableInterface : public UInterface
{
	GENERATED_BODY()
};

class ACTIONROGUELIKE_API ISRespawnableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Respawn();
};
