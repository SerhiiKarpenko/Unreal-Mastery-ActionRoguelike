#include "SAction.h"

void USAction::StartAction_Implementation(AActor* instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Running %s"), *GetNameSafe(this))
}

void USAction::StopAction_Implementation(AActor* instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Stop %s"), *GetNameSafe(this))
}

UWorld* USAction::GetWorld() const
{
	// outer is set when creating action via NewObject<T>
	UActorComponent* component =  Cast<UActorComponent>(GetOuter());

	if (component == nullptr)
		return nullptr;

	return component->GetWorld();
}
