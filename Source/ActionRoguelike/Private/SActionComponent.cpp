#include "SActionComponent.h"

USActionComponent::USActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USActionComponent::BeginPlay()
{
	Super::BeginPlay();
}


void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USActionComponent::AddAction(TSubclassOf<USAction> actionClass)
{
	if(!ensure(actionClass))
		return;

	USAction* usNewAction = NewObject<USAction>(this, actionClass);

	if (usNewAction == nullptr)
		return;

	Actions.Add(usNewAction);
}

bool USActionComponent::StartActionByName(AActor* instigator, FName actionName)
{
	for (USAction* action : Actions)
	{
		if ( action == nullptr || action->ActionName != actionName )
			continue;

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

		action->StopAction(instigator);
		return true;
	}
	
	return false;	
}



