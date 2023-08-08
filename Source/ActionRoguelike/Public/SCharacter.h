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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpellCast);

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacter();
	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);// here we bind all input

protected:

	UPROPERTY(BlueprintAssignable)
	FOnSpellCast OnSpellCast;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
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

	UPROPERTY(EditDefaultsOnly, Category = "Collision Chanels")
	TEnumAsByte<ECollisionChannel> ProjectileCollisionChanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USActionComponent* ActionComponent;
	
	void MoveForward(float value);
	void MoveRight(float value);
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void LookUpDown(const FInputActionValue& value);
	void LookLeftRight(const FInputActionValue& value);
	void PrimaryAttack();
	void BlackHoleAttack();
	void Teleport();
	void PrimaryInteract();
	void SprintStart();
	void SprintStop();
	
	UFUNCTION()
	void DisablePlayerInput();

	virtual void PostInitializeComponents() override;
	virtual FVector GetPawnViewLocation() const override;
};