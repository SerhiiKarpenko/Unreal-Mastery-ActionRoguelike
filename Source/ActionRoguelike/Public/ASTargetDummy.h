// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributeComponent.h"
#include "GameFramework/Actor.h"
#include "ASTargetDummy.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AASTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	AASTargetDummy();

protected:

	UPROPERTY(VisibleAnywhere)
	class USAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, USAttributeComponent* owningComponent, float NewHealth, float delta);
};
