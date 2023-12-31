
#pragma once

#include <string>

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SProjectileFactory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USProjectileFactory : public UActorComponent
{
	GENERATED_BODY()

public:	
	USProjectileFactory();

protected:
	
	UPROPERTY(EditAnywhere, Category= "Projectiles To Create")
	TSubclassOf<AActor> MagicProjectile;
	
	UPROPERTY(EditAnywhere, Category= "Projectiles To Create")
	TSubclassOf<AActor> BlackHoleProjectile;
	
	UPROPERTY(EditAnywhere, Category= "Projectiles To Create")
	TSubclassOf<AActor> TeleportProjectile;

public:
	AActor* CreateBlackHole(FTransform spawnPositionAndRotation, FActorSpawnParameters spawnParameters);
	AActor* CreateMagic(FTransform spawnPositionAndRotation, FActorSpawnParameters spawnParameters);
	AActor* CreateMagic(FVector spawnPosition, FRotator spawnRotation, FActorSpawnParameters spawnParameters);
	AActor* CreateTeleport(FTransform spawnPositionAndRotation, FActorSpawnParameters spawnParameters);
};
