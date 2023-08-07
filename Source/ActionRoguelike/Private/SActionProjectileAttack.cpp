#include "SActionProjectileAttack.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

USActionProjectileAttack::USActionProjectileAttack()
{
	ProjectileFactory = CreateDefaultSubobject<USProjectileFactory>("Projectile Factory");
	AttackAnimDelay = 0.2f;
	HandSocketName = "Muzzle_01";
}

void USActionProjectileAttack::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);

	ACharacter* character = Cast<ACharacter>(instigator);

	if(character == nullptr)
		return;
	
	character->PlayAnimMontage(AtackAniamtion);
	UGameplayStatics::SpawnEmitterAttached(CastingEffect, character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
	
	FTimerHandle TimerHandlePrimaryAttack;
	FTimerDelegate delegate;
	delegate.BindUFunction(this, "AttackDelayElapsed", character);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandlePrimaryAttack, delegate, AttackAnimDelay, false);
}

void USActionProjectileAttack::AttackDelayElapsed(ACharacter* instigatorCharacter)
{
	const FVector handLocation = instigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
	
	const FTransform SpawnTransformMatrix = FTransform(CalculateDirectionForProjectile(handLocation,
		Cast<APlayerController>(instigatorCharacter->GetController())), handLocation);
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = instigatorCharacter;

	ProjectileFactory->CreateMagic(SpawnTransformMatrix, SpawnParameters);
}

FRotator USActionProjectileAttack::CalculateDirectionForProjectile(FVector startProjectilePosition, APlayerController* controller)
{
	APlayerController* playerController = controller;
	
	FCollisionObjectQueryParams objectParameters;
	objectParameters.AddObjectTypesToQuery(ECC_WorldStatic);
	objectParameters.AddObjectTypesToQuery(ECC_WorldDynamic);
	objectParameters.AddObjectTypesToQuery(ECC_PhysicsBody);

	TArray<FHitResult> hitResults;
	
	FVector start = playerController->PlayerCameraManager->GetCameraLocation();
	FVector end = start + (playerController->PlayerCameraManager->GetCameraRotation().Vector() * 10000);
	
	GetWorld()->LineTraceMultiByObjectType(hitResults, start, end, objectParameters);

	if (hitResults.IsEmpty())
	{
		FVector direction = end - startProjectilePosition;
		direction.Normalize();
		
		return direction.Rotation();
	}
	
	for(FHitResult hit : hitResults)
	{
		FVector direction = hit.ImpactPoint - startProjectilePosition;
		direction.Normalize();
		
		return direction.Rotation();
	}

	FVector direction = end - startProjectilePosition;
	direction.Normalize();
		
	return  direction.Rotation();
}
