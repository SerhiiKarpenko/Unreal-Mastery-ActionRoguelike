#include "AI/SAICharacter.h"
#include "AIController.h"
#include "AudioDevice.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "SWorldUserWidget.h"
#include "AI/SAIController.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASAICharacter::ASAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Sensing Component");
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("Attribute Component");

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
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

	SetTarget(InstigatorActor);

	if (ActiveWidget != nullptr)
		return;
	
	ActiveWidget = CreateWidget<USWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
	ActiveWidget->AttachedActor = this;
	ActiveWidget->AddToViewport();
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
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
	
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