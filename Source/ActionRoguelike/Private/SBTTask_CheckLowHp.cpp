#include "SBTTask_CheckLowHp.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTTask_CheckLowHp::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* myController = OwnerComp.GetAIOwner();
	UBlackboardComponent* blackboardComponent = OwnerComp.GetBlackboardComponent();
	
	APawn* myPawn = myController->GetPawn();
	
	if(!ensure(myController) || blackboardComponent == nullptr || myPawn == nullptr)
		return;
	
	USAttributeComponent* attributes = USAttributeComponent::GetAttribute(myPawn);

	if (attributes == nullptr)
		return;
	
	bool isLowHP = attributes->GetHPPercent() <= 0.3f;

	blackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, isLowHP);
	
}



