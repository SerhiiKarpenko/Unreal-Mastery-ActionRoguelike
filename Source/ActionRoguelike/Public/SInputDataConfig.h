// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "SInputDataConfig.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USInputDataConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMove;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLook;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLookUpDown;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLookLeftRight;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Jump;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* BlackHoleAttack;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const UInputAction* Interact;
};
