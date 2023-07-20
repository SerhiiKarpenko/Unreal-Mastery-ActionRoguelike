// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "SInteractionComponent.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SProjectileFactory.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Atack") // give as a possibility to change it anywhere we want,
	TSubclassOf<AActor> ProjectileClass; // give as a field where we can pass the reference to another class,

	UPROPERTY(EditAnywhere, Category = "Atack")
	UAnimMontage* AtackAniamtion;
	FTimerHandle TimerHandlePrimaryAttack;

public:
	// Sets default values for this character's properties
	// works firstly, BeginPlayer works after all components and etc is initialized, but constructor works first
	ASCharacter();
	

protected:

	virtual void BeginPlay() override; // works like a start method in unity

public:	
	virtual void Tick(float DeltaTime) override; // works like an update method in unity

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // here we bind all input

protected:
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere) // UPROPERTY gives us visible component everywhere
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class USInputDataConfig* InputDataConfig;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " Enhanced Input ")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(VisibleAnywhere, Category = "Projectile Factory")
	class USProjectileFactory* ProjectileFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	class USAttributeComponent* AttributeComponent;

	void MoveForward(float value);
	void MoveRight(float value);
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void LookUpDown(const FInputActionValue& value);
	void LookLeftRight(const FInputActionValue& value);
	void PrimaryAttackTimeElapsed();
	void PrimaryAttack();
	void BlackHoleAttack();
	void TeleportElapsed();
	void Teleport();
	void PrimaryInteract();
	FRotator CalculateDirectionForProjectile(FVector startProjectilePosition);
};