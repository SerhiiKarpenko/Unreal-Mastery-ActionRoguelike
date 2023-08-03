// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackHoleProjectile.h"

#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "SBaseProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASBlackHoleProjectile::ASBlackHoleProjectile()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("Radial Force Component");
	RadialForceComponent->SetupAttachment(ProjectileSphereComponent);


	SphereComponentToCollectOverlappedObjects = CreateDefaultSubobject<USphereComponent>("Sphere Component For Collisions");
	SphereComponentToCollectOverlappedObjects->SetupAttachment(ProjectileSphereComponent);
	SphereComponentToCollectOverlappedObjects->SetSphereRadius(1300);
	SphereComponentToCollectOverlappedObjects->SetCollisionProfileName("BlackHole");
	
	RadialForceComponent->Radius = 1300;
	RadialForceComponent->ForceStrength = -900000.0f;
	RadialForceComponent->ImpulseStrength = 300000.0f;
	RadialForceComponent->RemoveObjectTypeToAffect(ObjectTypeQuery3);

	ProjectileSphereComponent->SetCollisionProfileName("BlackHole");
	ProjectileMovementComponent->InitialSpeed = 500.0f;

	ConstantBlackHoleDamage = 0.1f;
	ExplosionBlackHoleDamage = 20;

}

void ASBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASBlackHoleProjectile::DestroyObjects);
	OnDestroyed.AddDynamic(this, &ASBlackHoleProjectile::OnBlackHoleDestroy);
}

void ASBlackHoleProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponentToCollectOverlappedObjects->OnComponentBeginOverlap.AddDynamic(this, &ASBlackHoleProjectile::CollectOverlappedObjects);
	SphereComponentToCollectOverlappedObjects->OnComponentEndOverlap.AddDynamic(this, &ASBlackHoleProjectile::RemoveOverlappedObject);
}

void ASBlackHoleProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ArrayOfAttributes.Num() <= 0)
		return;

	for(int i = ArrayOfAttributes.Num() - 1; i >= 0; i--)
	{
		if(!ArrayOfAttributes[i]->IsAlive())
		{
			ArrayOfAttributes.RemoveAt(i);

			if (ArrayOfAttributes.Num() <= 0)
				break;
				
			continue;
		}

		ArrayOfAttributes[i]->ApplyDamage(GetInstigator(), -ConstantBlackHoleDamage);
	}
}

void ASBlackHoleProjectile::DestroyObjects(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!OtherComp->IsSimulatingPhysics())
		return;
	
	OtherActor->Destroy();
}

void ASBlackHoleProjectile::CollectOverlappedObjects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor == GetInstigator())
		return;
	
	USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttribute(OtherActor);

	if( AttributeComponent == nullptr)
		return;

	ArrayOfAttributes.Add(AttributeComponent);
}

void ASBlackHoleProjectile::RemoveOverlappedObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == GetInstigator())
		return;
	
	USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttribute(OtherActor);

	if( AttributeComponent == nullptr)
		return;

	if(!ArrayOfAttributes.Contains(AttributeComponent))
		return;
		
	ArrayOfAttributes.RemoveSingle(AttributeComponent);
}

void ASBlackHoleProjectile::OnBlackHoleDestroy(AActor* destoryedACtor)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ParticleSystem, GetActorLocation(), GetActorRotation());
	RadialForceComponent->FireImpulse();

	for(int i = ArrayOfAttributes.Num() - 1; i >= 0; i--)
	{
		if(!ArrayOfAttributes[i]->IsAlive())
		{
			ArrayOfAttributes.RemoveAt(i);

			if (ArrayOfAttributes.Num() <= 0)
				break;
				
			continue;
		}
		
		ArrayOfAttributes[i]->ApplyDamage(GetInstigator(), -ExplosionBlackHoleDamage);
	}
}




