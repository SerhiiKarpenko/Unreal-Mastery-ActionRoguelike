#include "SAttributeComponent.h"

USAttributeComponent::USAttributeComponent()
{
	Health = 100;
}

bool USAttributeComponent::ApplyDamage(float damageToApply)
{
	if (Health <= 0)
		return false;
	
	if (abs(damageToApply) >= Health)
	{
		Health = 0;
		OnHealthChanged.Broadcast(nullptr, this, Health, damageToApply);
		return false;
	}
	
	Health += damageToApply;
	OnHealthChanged.Broadcast(nullptr, this, Health, damageToApply);
	return true;
}

