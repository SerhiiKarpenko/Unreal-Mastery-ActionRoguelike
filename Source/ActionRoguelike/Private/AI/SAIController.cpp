#include "AI/SAIController.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("Behavior Tree Is nullptr, pls assing behavior tree in your AI controller")))
	{
		RunBehaviorTree(BehaviorTree);
	}

	
	/*
	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	
	if (playerPawn == nullptr)
		return;

	GetBlackboardComponent()->SetValueAsObject("TargetActor", playerPawn);
*/
	
}
