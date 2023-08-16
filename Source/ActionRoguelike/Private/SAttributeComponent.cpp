#include "SAttributeComponent.h"
#include "SGameModeBase.h"
#include "Net/UnrealNetwork.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("ar.DamageMultiplier"), 1.0f,
	TEXT("Global damage multiplier for Attribute Component"),ECVF_Cheat);


USAttributeComponent::USAttributeComponent()
{
	Health = MaxHealth;

	SetIsReplicatedByDefault(true);
}

bool USAttributeComponent::ApplyDamage(AActor* instigatorActor, float damageToApply)
{
	if (Health <= 0)
		return false;

	float damageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
	damageToApply *= damageMultiplier;
	
	if (abs(damageToApply) >= Health)
	{
		Health = 0;
		
		OnHealthChanged.Broadcast(instigatorActor, this, Health, damageToApply);
		//MulticastHealthChanged(instigatorActor, Health, damageMultiplier);
		Die(instigatorActor);
		
		return false;
	}
	
	Health += damageToApply;
	OnHealthChanged.Broadcast(instigatorActor, this, Health, damageToApply);
	//MulticastHealthChanged(instigatorActor, Health, damageMultiplier);
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
		//MulticastHealthChanged(InstigatorActor, Health, healToApply);
		return true;
	}
	
	Health += healToApply;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, healToApply);
	//MulticastHealthChanged(InstigatorActor, Health, healToApply);
	return true;
}


bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

void USAttributeComponent::Die(AActor* Instigator)
{
	OnDie.Broadcast();
	isAlive = false;
	ASGameModeBase* gameModeBase = GetWorld()->GetAuthGameMode<ASGameModeBase>();
	
	if (gameModeBase == nullptr)
		return;

	gameModeBase->OnActorKilled(GetOwner(), Instigator);
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

bool USAttributeComponent::Kill(AActor* instigator)
{
	return ApplyDamage(instigator, -MaxHealth);
}

float USAttributeComponent::GetMaxHP()
{
	return MaxHealth;
}

float USAttributeComponent::GetHP()
{
	return Health;
}

float USAttributeComponent::GetHPPercent()
{
	return Health/MaxHealth;
}

void USAttributeComponent::ResetHP()
{
	Health = MaxHealth;
	OnHealthChanged.Broadcast(GetOwner(), this, Health, 0);
}

void USAttributeComponent::MulticastHealthChanged_Implementation(AActor* instigator, float newHealth,float healthChange)
{
	OnHealthChanged.Broadcast(instigator, this, newHealth, healthChange);
}

void USAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAttributeComponent, Health);
	DOREPLIFETIME(USAttributeComponent, MaxHealth);
	
	//DOREPLIFETIME_CONDITION(USAttributeComponent, MaxHealth, COND_InitialOnly);
}



