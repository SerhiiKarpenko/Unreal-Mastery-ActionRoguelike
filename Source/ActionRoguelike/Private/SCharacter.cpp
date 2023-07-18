// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "SInputDataConfig.h"
#include "ActionRoguelike/Public/SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputActionValue.h"

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

}

void ASCharacter::BeginPlay() // unit start method
{
	Super::BeginPlay();
	
}

void ASCharacter::Tick(float DeltaTime)  // unity update method
{
	Super::Tick(DeltaTime);

}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) // here we bind an input
{
	/*Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	*/
	
	APlayerController* PC = Cast<APlayerController>(GetController());
 
	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	PEI->BindAction(InputDataConfig->InputMove, ETriggerEvent::Triggered, this, &ASCharacter::Move);
	PEI->BindAction(InputDataConfig->Jump, ETriggerEvent::Started, this, &ASCharacter::Jump);
	
	PEI->BindAction(InputDataConfig->InputLookUpDown, ETriggerEvent::Triggered, this, &ASCharacter::LookUpDown);
	PEI->BindAction(InputDataConfig->InputLookLeftRight, ETriggerEvent::Triggered, this, &ASCharacter::LookLeftRight);
	
	PEI->BindAction(InputDataConfig->Attack, ETriggerEvent::Started, this, &ASCharacter::PrimaryAttack);
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
	PlayAnimMontage(AtackAniamtion);

	GetWorldTimerManager().SetTimer(TimerHandlePrimaryAttack, this, &ASCharacter::PrimaryAtackTimeElapsed, 0.2f);

	//this one is stopping attack timer, for exmp if player died we just clearing the timer
	//GetWorldTimerManager().ClearTimer(TimerHandlePrimaryAttack); 
	
}

void ASCharacter::PrimaryAtackTimeElapsed()
{
	FVector handLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform SpawnTransformMatrix = FTransform(GetControlRotation(),handLocation);
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransformMatrix, SpawnParameters);
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComponent == nullptr)
		return;
	
	//InteractionComponent->PrimaryInteract();
	InteractionComponent->SecondInteract();
}


