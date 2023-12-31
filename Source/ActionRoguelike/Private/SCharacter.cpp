// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "SInputDataConfig.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "SActionComponent.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

ASCharacter::ASCharacter() // constructor
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>("Interaction Component");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	ProjectileFactory = CreateDefaultSubobject<USProjectileFactory>("Projectile Factory");
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("Attributes Component");
	ActionComponent = CreateDefaultSubobject<USActionComponent>("Action Component");

}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComponent->OnDie.AddDynamic(this, &ASCharacter::DisablePlayerInput);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	return CameraComponent->GetComponentLocation();
}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) // here we bind an input
{
	APlayerController* PC = Cast<APlayerController>(GetController());
 
	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInputComponent->BindAction(InputDataConfig->InputMove, ETriggerEvent::Triggered, this, &ASCharacter::Move);
	EnhancedInputComponent->BindAction(InputDataConfig->Jump, ETriggerEvent::Started, this, &ASCharacter::Jump);
	EnhancedInputComponent->BindAction(InputDataConfig->InputLookUpDown, ETriggerEvent::Triggered, this, &ASCharacter::LookUpDown);
	EnhancedInputComponent->BindAction(InputDataConfig->InputLookLeftRight, ETriggerEvent::Triggered, this, &ASCharacter::LookLeftRight);
	EnhancedInputComponent->BindAction(InputDataConfig->Attack, ETriggerEvent::Started, this, &ASCharacter::PrimaryAttack);
	EnhancedInputComponent->BindAction(InputDataConfig->BlackHoleAttack, ETriggerEvent::Started, this, &ASCharacter::BlackHoleAttack);
	EnhancedInputComponent->BindAction(InputDataConfig->Teleport, ETriggerEvent::Started, this, &ASCharacter::Teleport);
	EnhancedInputComponent->BindAction(InputDataConfig->Interact, ETriggerEvent::Started, this, &ASCharacter::PrimaryInteract);
	EnhancedInputComponent->BindAction(InputDataConfig->Sprint, ETriggerEvent::Started, this, &ASCharacter::SprintStart);
	EnhancedInputComponent->BindAction(InputDataConfig->Sprint, ETriggerEvent::Completed, this, &ASCharacter::SprintStop);
}

void ASCharacter::MoveForward(float value)
{
	FRotator ControlRotation = GetControlRotation();
	
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	
	AddMovementInput(ControlRotation.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator controlRotation = GetControlRotation();
	
	controlRotation.Pitch = 0.0f;
	controlRotation.Roll = 0.0f;

	// x = forwad
	// y = right
	// z = up
	
	FVector rightVector = FRotationMatrix(controlRotation).GetScaledAxis(EAxis::Y); // if there a kismetmathlibrary, this is a part of blueprint math
	
	AddMovementInput(rightVector, value);
}

void ASCharacter::Move(const FInputActionValue& value)
{
	if (Controller == nullptr)
		return;

	const FVector2D moveValue = value.Get<FVector2D>();
	FRotator controlRotation = GetControlRotation();
	
	controlRotation.Pitch = 0.0f;
	controlRotation.Roll = 0.0f;

	const FVector rightVector = FRotationMatrix(controlRotation).GetScaledAxis(EAxis::Y); // if there a kismetmathlibrary, this is a part of blueprint math

	if (moveValue.Y != 0.0f)
		AddMovementInput(controlRotation.Vector(), moveValue.Y);
	
	if (moveValue.X != 0.0f)
		AddMovementInput(rightVector, moveValue.X);
}

void ASCharacter::Look(const FInputActionValue& value)
{
	if (Controller == nullptr)
		return;

	const FVector2D lookValue = value.Get<FVector2D>();

	if (lookValue.X != 0.0f)
		AddControllerYawInput(lookValue.X);
	
	if (lookValue.Y != 0.0f)
		AddControllerPitchInput(lookValue.Y);
}

void ASCharacter::LookUpDown(const FInputActionValue& value)
{
	if (Controller == nullptr)
		return;

	const float lookValue = value.Get<float>();

	if (lookValue == 0.0f)
		return;
	
	AddControllerPitchInput(lookValue);
}

void ASCharacter::LookLeftRight(const FInputActionValue& value)
{
	if (Controller == nullptr)
		return;

	const float lookValue = value.Get<float>();

	if (lookValue == 0.0f)
		return;
	
	AddControllerYawInput(lookValue);
}

void ASCharacter::PrimaryAttack()
{
	ActionComponent->StartActionByName(this, "PrimaryAttack");
}


void ASCharacter::PrimaryInteract()
{
	if (InteractionComponent == nullptr)
		return;
	
	//InteractionComponent->PrimaryInteract();
	InteractionComponent->SecondInteract();
}


void ASCharacter::BlackHoleAttack()
{
	ActionComponent->StartActionByName(this, "Blackhole");
}

void ASCharacter::Teleport()
{
	ActionComponent->StartActionByName(this, "Teleport");
}


void ASCharacter::DisablePlayerInput()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());
	DisableInput(playerController);
}

void ASCharacter::HealSelf(float Amount)
{
	AttributeComponent->Heal(this, Amount);
}

void ASCharacter::SprintStart()
{
	ActionComponent->StartActionByName(this, "Sprint");
}

void ASCharacter::SprintStop()
{
	ActionComponent->StopActionByName(this, "Sprint");
}
