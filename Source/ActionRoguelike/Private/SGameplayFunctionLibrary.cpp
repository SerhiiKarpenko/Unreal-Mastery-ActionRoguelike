#include "SGameplayFunctionLibrary.h"
#include "SAttributeComponent.h"

bool USGameplayFunctionLibrary::ApplyDamage(AActor* damageCauser, AActor* targetActor, float damageAmount)
{
	USAttributeComponent* targetActorAttributes = USAttributeComponent::GetAttribute(targetActor);

	if(targetActorAttributes == nullptr)
		return false;

	return targetActorAttributes->ApplyDamage(damageCauser, -damageAmount);
}

bool USGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* damageCauser, AActor* targetActor, float damageAmount,const FHitResult& hitResult)
{
	if (!ApplyDamage(damageCauser, targetActor, damageAmount))
			return false;

	UPrimitiveComponent* hitComponent = hitResult.GetComponent();
	
	if(hitComponent == nullptr && !hitComponent->IsSimulatingPhysics(hitResult.BoneName))
		return false;

	//hitComponent->AddImpulseAtLocation(-hitResult.ImpactNormal * 300000.f, hitResult.ImpactPoint, hitResult.BoneName);
	
	return true;
}
