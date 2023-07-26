#include "SMagicProjectile.h"
#include "SAttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASMagicProjectile::ASMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	
	//SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);
	//SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
	SphereComponent->SetCollisionProfileName("Projectile");
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnOverlapWithActor);
	
	RootComponent = SphereComponent;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("Particle System Component");
	ParticleSystemComponent->SetupAttachment(SphereComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio component");
	AudioComponent->SetupAttachment(SphereComponent);
}


void ASMagicProjectile::OnOverlapWithActor(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == nullptr || OtherActor == GetInstigator())
		return;

	USAttributeComponent* actorsAttributes = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (actorsAttributes == nullptr)
		return;

	actorsAttributes->ApplyDamage(-20.0);
	
	AudioComponent->Stop();
	APawn* player = GetInstigator();

	if (player != nullptr)
	{
		UCameraComponent* ComponentByClass = Cast<UCameraComponent>(player->GetComponentByClass(UCameraComponent::StaticClass()));

		if (ComponentByClass != nullptr)
			UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake, ComponentByClass->GetComponentLocation(), 50, 50);
	}
	
	AudioComponent->DestroyComponent();
	
	Destroy();
}

