#include "AI/SBTTaskNode_RangedAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTaskNode_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();

	if (!ensure(MyController))
		return EBTNodeResult::Failed;
		
	ACharacter* MyCharacter = Cast<ACharacter>(MyController->GetPawn());

	if (MyCharacter == nullptr)
		return EBTNodeResult::Failed;

	FVector muzzleLocation = MyCharacter->GetMesh()->GetSocketLocation("Muzzle_01");

	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));

	if (target == nullptr)
		return EBTNodeResult::Failed;

	FVector direction = target->GetActorLocation() - muzzleLocation;
	FRotator muzzleRotation = direction.Rotation();

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* newProjectile = GetWorld()->SpawnActor<AActor>(Projectile, muzzleLocation, muzzleRotation, params);

	return newProjectile != nullptr ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;  
}
