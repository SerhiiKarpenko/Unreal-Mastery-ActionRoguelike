#include "ASTargetDummy.h"

AASTargetDummy::AASTargetDummy()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	RootComponent = StaticMeshComponent;

	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("Attributes component");
	AttributeComponent->OnHealthChanged.AddDynamic(this, &AASTargetDummy::OnHealthChange);

}

void AASTargetDummy::OnHealthChange(AActor* InstigatorActor, USAttributeComponent* owningComponent, float NewHealth, float delta)
{
	if (delta > 0)
		return;
	
	StaticMeshComponent->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);	
}

