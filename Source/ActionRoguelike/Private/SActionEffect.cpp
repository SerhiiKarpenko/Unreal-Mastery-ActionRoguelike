

#include "SActionEffect.h"

#include "SActionComponent.h"

USActionEffect::USActionEffect()
{
	AutoStart = true;
}

void USActionEffect::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);

	if (Duration > 0.0f)
	{
		FTimerDelegate delegate;
		delegate.BindUFunction(this, "StopAction", instigator);

		GetWorld()->GetTimerManager().SetTimer(DurationHandle, delegate, Duration, false);
	}

	if (Frequency > 0.0f)
	{
		FTimerDelegate delegate;
		delegate.BindUFunction(this, "ExecuteEffect", instigator);

		GetWorld()->GetTimerManager().SetTimer(FrequencyHandle, delegate, Frequency, true);
	}
}

void USActionEffect::StopAction_Implementation(AActor* instigator)
{
	if (GetWorld()->GetTimerManager().GetTimerRemaining(FrequencyHandle) < KINDA_SMALL_NUMBER)
		ExecuteEffect(instigator);
		
	Super::StopAction_Implementation(instigator);
	
	GetWorld()->GetTimerManager().ClearTimer(FrequencyHandle);
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);

	USActionComponent* owningComponent = GetOwningComponent();

	if (owningComponent == nullptr)
		return;

	owningComponent->RemoveAction(this);
}

void USActionEffect::ExecuteEffect_Implementation(AActor* instigator)
{
	
}
