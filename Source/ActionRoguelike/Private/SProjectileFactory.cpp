

#include "SProjectileFactory.h"

USProjectileFactory::USProjectileFactory()
{
	PrimaryComponentTick.bCanEverTick = true;
}


AActor* USProjectileFactory::CreateBlackHole(FTransform spawnPositionAndRotation, FActorSpawnParameters spawnParameters)
{
	return GetWorld()->SpawnActor<AActor>(BlackHoleProjectile, spawnPositionAndRotation, spawnParameters);
}

AActor* USProjectileFactory::CreateMagic(FTransform spawnPositionAndRotation, FActorSpawnParameters spawnParameters)
{
	return GetWorld()->SpawnActor<AActor>(MagicProjectile, spawnPositionAndRotation, spawnParameters);
}

AActor* USProjectileFactory::CreateTeleport(FTransform spawnPositionAndRotation, FActorSpawnParameters spawnParameters)
{
	return GetWorld()->SpawnActor<AActor>(TeleportProjectile, spawnPositionAndRotation, spawnParameters);
}



