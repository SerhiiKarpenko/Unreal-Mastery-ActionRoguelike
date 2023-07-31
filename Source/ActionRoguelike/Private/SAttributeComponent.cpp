#include "SAttributeComponent.h"

USAttributeComponent::USAttributeComponent()
{
	Health = 100;
}

bool USAttributeComponent::ApplyDamage(AActor* instigatorActor, float damageToApply)
{
	if (Health <= 0)
		return false;
	
	if (abs(damageToApply) >= Health)
	{
		if (IsAlive())
			Die();
		
		Health = 0;
		OnHealthChanged.Broadcast(instigatorActor, this, Health, damageToApply);
		return false;
	}
	
	Health += damageToApply;
	OnHealthChanged.Broadcast(instigatorActor, this, Health, damageToApply);
	return true;
}

bool USAttributeComponent::Heal(AActor* InstigatorActor ,float healToApply)
{
	if (Health == MaxHealth || !IsAlive())
		return false;
	
	if(Health + healToApply >= MaxHealth)
	{
		Health = MaxHealth;
		OnHealthChanged.Broadcast(InstigatorActor, this, Health, healToApply);
		return true;
	}
	
	Health += healToApply;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, healToApply);
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

