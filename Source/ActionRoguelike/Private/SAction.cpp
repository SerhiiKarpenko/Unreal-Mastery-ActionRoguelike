#include "SAction.h"

#include "SActionComponent.h"

void USAction::StartAction_Implementation(AActor* instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Running %s"), *GetNameSafe(this));

	USActionComponent* owningComponent = GetOwningComponent();

	if (owningComponent == nullptr)
		return;

	owningComponent->ActiveGameplayTags.AppendTags(GrantsTags);
	isRunning = true;
}

void USAction::StopAction_Implementation(AActor* instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Stop %s"), *GetNameSafe(this));

	ensureAlways(isRunning);
	
	USActionComponent* owningComponent = GetOwningComponent();

	if (owningComponent == nullptr)
		return;

	owningComponent->ActiveGameplayTags.RemoveTags(GrantsTags);
	isRunning = false;
}

UWorld* USAction::GetWorld() const
{
	// outer is set when creating action via NewObject<T>
	UActorComponent* component =  Cast<UActorComponent>(GetOuter());

	if (component == nullptr)
		return nullptr;

	return component->GetWorld();
}

USActionComponent* USAction::GetOwningComponent() const
{
	return Cast<USActionComponent>(GetOuter());	
}

bool USAction::CanStart_Implementation(AActor* instigator)
{
	USActionComponent* owningComponent = GetOwningComponent();
	return !owningComponent->ActiveGameplayTags.HasAny(BlockedTags);
}

bool USAction::IsRunning() const
{
	return isRunning;
}
