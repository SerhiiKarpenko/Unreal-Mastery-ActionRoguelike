// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "SAICharacter.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASAICharacter();

protected:

	void SetTarget(AActor* newTarget);
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class USAttributeComponent* AttributeComponent;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void DamageTaken(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float HealthChange);
	
	UFUNCTION()
	void OnDie();
	

	
	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
};
