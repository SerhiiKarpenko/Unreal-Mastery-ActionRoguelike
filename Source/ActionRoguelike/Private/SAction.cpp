#include "SAction.h"

void USAction::StartAction_Implementation(AActor* instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Running %s"), *GetNameSafe(this))
}

void USAction::StopAction_Implementation(AActor* instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Stop %s"), *GetNameSafe(this))
}
