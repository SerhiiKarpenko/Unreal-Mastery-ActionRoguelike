// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// check distance between AI pawn and target actor

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (!ensure(BlackboardComponent))
	{
		return;	
	}

	AActor* targetActor = Cast<AActor>( BlackboardComponent->GetValueAsObject("TargetActor"));
	
	if (targetActor == nullptr)
		return;

	AAIController* controller = OwnerComp.GetAIOwner();

	if(!ensure(controller))
		return;

	APawn* pawn = controller->GetPawn();

	if (!ensure(pawn))
		return;

	float distanceTo = FVector::Distance(targetActor->GetActorLocation(), pawn->GetActorLocation());
	bool bWithinRange = distanceTo < 2000.0f;

	bool bLineOfSightTo = false;
	
	if (bWithinRange)
		bLineOfSightTo = controller->LineOfSightTo(targetActor);

	BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bLineOfSightTo);
}
