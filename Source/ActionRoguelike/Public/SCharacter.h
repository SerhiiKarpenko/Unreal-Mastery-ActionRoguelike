// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere) // give as a possibility to change it anywhere we want,
	TSubclassOf<AActor> ProjectileClass; // give as a field where we can pass the reference to another class,
	
public:
	// Sets default values for this character's properties
	// works firstly, BeginPlayer works after all components and etc is initialized, but constructor works first
	ASCharacter();
	

protected:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere) // UPROPERTY gives us visible component everywhere
	USpringArmComponent* SpringArmComponent; 

	virtual void BeginPlay() override; // works like a start method in unity
	
	void MoveForward(float value); // my methhods
	void MoveRight(float value);
	void PrimaryAttack();

public:	
	virtual void Tick(float DeltaTime) override; // works like an update method in unity

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // here we bind all input

};
