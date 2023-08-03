// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTTaskNode_Heal.h"

#include "AIController.h"
#include "SAttributeComponent.h"

EBTNodeResult::Type USBTTaskNode_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* aiController = OwnerComp.GetAIOwner();
	APawn* Pawn = aiController->GetPawn();

	USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttribute(Pawn);

	if (AttributeComponent == nullptr )
		return EBTNodeResult::Failed;

	AttributeComponent->Heal(Pawn, 10);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
