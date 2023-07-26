#include "AI/SAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);

	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	
	if (playerPawn == nullptr)
		return;

	GetBlackboardComponent()->SetValueAsObject("TargetActor", playerPawn);
}
