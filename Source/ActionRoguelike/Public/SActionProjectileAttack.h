#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SProjectileFactory.h"
#include "SActionProjectileAttack.generated.h"

UCLASS()
class ACTIONROGUELIKE_API USActionProjectileAttack : public USAction
{
	GENERATED_BODY()
public:
	USActionProjectileAttack();

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	class USProjectileFactory* ProjectileFactory;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	FName HandSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AtackAniamtion;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	class UParticleSystem* CastingEffect;

	UFUNCTION()
	void AttackDelayElapsed(ACharacter* instigatorCharacter);

	FRotator USActionProjectileAttack::CalculateDirectionForProjectile(FVector startProjectilePosition, APlayerController* controller);
public:

	virtual void StartAction_Implementation(AActor* instigator) override;
};
