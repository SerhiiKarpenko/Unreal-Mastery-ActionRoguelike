#include "SAttributeComponent.h"

USAttributeComponent::USAttributeComponent()
{
	Health = 100;
}

bool USAttributeComponent::ApplyDamage(float damageToApply)
{
	Health += damageToApply;
	OnHealthChanged.Broadcast(nullptr, this, Health, damageToApply);
	return true;
}

