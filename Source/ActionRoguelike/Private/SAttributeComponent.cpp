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
		if (IsAlive())
			Die();
		
		Health = 0;
		OnHealthChanged.Broadcast(nullptr, this, Health, damageToApply);
		return false;
	}
	
	Health += damageToApply;
	OnHealthChanged.Broadcast(nullptr, this, Health, damageToApply);
	return true;
}


bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

void USAttributeComponent::Die()
{
	OnDie.Broadcast();
	isAlive = false;
}

