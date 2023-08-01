#include "SAttributeComponent.h"

USAttributeComponent::USAttributeComponent()
{
	Health = MaxHealth;
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

USAttributeComponent* USAttributeComponent::GetAttribute(AActor* fromActor)
{
	if (fromActor == nullptr)
		return nullptr;

	return Cast<USAttributeComponent>(fromActor->GetComponentByClass(StaticClass()));
	
}

bool USAttributeComponent::IsActorAlive(AActor* actor)
{
	USAttributeComponent* attributeComponent = GetAttribute(actor);

	if (attributeComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot check if %s is alive because actor have no attributes component"),
		       *actor->GetName());
		
		return false;
	}

	return attributeComponent->IsAlive();
}



