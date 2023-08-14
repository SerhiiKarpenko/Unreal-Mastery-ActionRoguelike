#include "SMagicProjectile.h"

#include "SActionComponent.h"
#include "SGameplayFunctionLibrary.h"
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
	ProjectileMovementComponent->InitialSpeed = 2000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio component");
	AudioComponent->SetupAttachment(SphereComponent);
	DamageAmount = 20.0f;

	SetReplicates(true);
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

	/*USAttributeComponent* actorsAttributes = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (actorsAttributes == nullptr)
		return;

	actorsAttributes->ApplyDamage(GetInstigator(), -20.0);
	*/

	USActionComponent* actionComponent = Cast<USActionComponent>(OtherActor->GetComponentByClass(USActionComponent::StaticClass()));
	
	if (actionComponent != nullptr && actionComponent->ActiveGameplayTags.HasTag(ParryTag))
	{
		ProjectileMovementComponent->Velocity = -ProjectileMovementComponent->Velocity;
		SetInstigator(Cast<APawn>(OtherActor));
		DamageAmount = 4.0f;
		return;
	}

	if(!USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult) )
		return;

	if (actionComponent != nullptr)
	{
		actionComponent->AddAction(GetInstigator(), burningActionEffect);
	}
	
	AudioComponent->Stop();
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake, GetActorLocation(), 50, 50);
	
	AudioComponent->DestroyComponent();
	UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
	
	Destroy();
}

