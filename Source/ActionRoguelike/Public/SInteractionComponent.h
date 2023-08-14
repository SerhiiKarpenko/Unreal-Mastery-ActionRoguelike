// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWorldUserWidget.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USInteractionComponent();

protected:
	
	virtual void BeginPlay() override;
	void FindBestInteractable();

	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USWorldUserWidget> DefaultWidgetClass;
	
	UPROPERTY()
	class USWorldUserWidget* DefaultWidgetInstance;


	//-------------------NET WORKING--------------------//
	
	// Reliable = will always arrive, eventually. Request will be re-sent unless an acknowledgment was received
	// Unreliable = not guaranteed, packet can get lost and wont retry
	
	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* inFocus);
	
public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool CrateInteractionWidget();
	void PrimaryInteract();
	void SecondInteract();


private:
	
	float _interactionDistance;
	AActor* _previousFocusedActor;
};
