#include "AI/SAICharacter.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "AI/SAIController.h"

ASAICharacter::ASAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Sensing Component");
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("Attribute Component");
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
	AttributeComponent->OnDie.AddDynamic(this, &ASAICharacter::OnDie);
	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASAICharacter::DamageTaken);
}

void ASAICharacter::DamageTaken(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float HealthChange)
{
	if (HealthChange >= 0)
		return;

	if (NewHealth <= 0)
		return;

	if (InstigatorActor == this)
		return;

	SetTarget(this);
}

void ASAICharacter::OnDie()
{
	// stop the behaviour tree
	AAIController* aiController = Cast<AAIController>(GetController());

	if (aiController != nullptr)
		aiController->GetBrainComponent()->StopLogic("Killed");
	
	// ragdoll
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll"); // prevents falling through the floor when killed
	
	// set lifespan // how l
	SetLifeSpan(10.0f);
}

void ASAICharacter::SetTarget(AActor* newTarget)
{
	ASAIController* aiController = GetController<ASAIController>();

	if (aiController == nullptr)
		return;

	aiController->GetBlackboardComponent()->SetValueAsObject("TargetActor",  newTarget);
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTarget(Pawn);
	DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER_SPOTTED", nullptr, FColor::White, 4.0f, true);
}





