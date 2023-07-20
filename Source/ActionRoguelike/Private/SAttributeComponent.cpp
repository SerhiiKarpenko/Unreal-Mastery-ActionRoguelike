#include "SAttributeComponent.h"

USAttributeComponent::USAttributeComponent()
{
	Health = 100;
}

bool USAttributeComponent::ApplyDamage(float damageToApply)
{
	Health += damageToApply;
	return true;
}

