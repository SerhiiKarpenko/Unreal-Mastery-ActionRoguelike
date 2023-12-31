#include "SActionComponent.h"

USActionComponent::USActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for (TSubclassOf<USAction> action : DefaultActions)
	{
		AddAction(GetOwner(), action);
	}
}

void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString debugMessage = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, debugMessage);
}

void USActionComponent::AddAction(AActor* instigator,TSubclassOf<USAction> actionClass)
{
	if(!ensure(actionClass))
		return;

	USAction* usNewAction = NewObject<USAction>(this, actionClass);

	if (usNewAction == nullptr)
		return;

	Actions.Add(usNewAction);

	if (usNewAction->AutoStart && usNewAction->CanStart(instigator))
		usNewAction->StartAction(instigator);
}

void USActionComponent::RemoveAction(USAction* UsActionEffect)
{
	if (UsActionEffect == nullptr && !UsActionEffect->IsRunning())
		return;

	Actions.Remove(UsActionEffect);
}

bool USActionComponent::StartActionByName(AActor* instigator, FName actionName)
{
	for (USAction* action : Actions)
	{
		if ( action == nullptr || action->ActionName != actionName )
			continue;

		if (!action->CanStart(instigator))
		{
			FString failedMSG = FString::Printf(TEXT("Failed to run %s"), *actionName.ToString());
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, failedMSG);
			
			continue;
		}

		//is client ? 
		if (!GetOwner()->HasAuthority())
			ServerStartAction(instigator, actionName);

		action->StartAction(instigator);
		return true;
	}
	
	return false;
}

bool USActionComponent::StopActionByName(AActor* instigator, FName actionName)
{
	for (USAction* action : Actions)
	{
		if ( action == nullptr || action->ActionName != actionName )
			continue;

		if (!action->IsRunning())
			continue;

		if (!GetOwner()->HasAuthority())
			ServerStopAction(instigator, actionName);
		
		action->StopAction(instigator);
		return true;
	}
	
	return false;	
}

void USActionComponent::ServerStartAction_Implementation(AActor* instigator, FName actionName)
{
	StartActionByName(instigator, actionName);
}

void USActionComponent::ServerStopAction_Implementation(AActor* instigator, FName actionName)
{
	StopActionByName(instigator, actionName);
}



