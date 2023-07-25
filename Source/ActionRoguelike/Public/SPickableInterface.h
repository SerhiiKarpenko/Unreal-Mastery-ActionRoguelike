// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SPickableInterface.generated.h"

UINTERFACE(MinimalAPI)
class USPickableInterface : public UInterface
{
	GENERATED_BODY()
};

class ACTIONROGUELIKE_API ISPickableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pickup(APawn* InstigatorPawn);
};
