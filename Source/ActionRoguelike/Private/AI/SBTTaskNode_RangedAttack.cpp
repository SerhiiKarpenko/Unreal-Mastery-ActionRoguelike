#include "AI/SBTTaskNode_RangedAttack.h"
#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

USBTTaskNode_RangedAttack::USBTTaskNode_RangedAttack()
{
	MaxBulletSpread = 0.8f;
}

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

	if( !USAttributeComponent::IsActorAlive(target) )
	{
		return EBTNodeResult::Failed;
	}

	FVector direction = target->GetActorLocation() - muzzleLocation;
	FRotator muzzleRotation = direction.Rotation();

	muzzleRotation.Pitch += FMath::RandRange(0.0f, MaxBulletSpread);
	muzzleRotation.Yaw += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);
	
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	params.Instigator = MyController->GetPawn();

	AActor* newProjectile = GetWorld()->SpawnActor<AActor>(Projectile, muzzleLocation, muzzleRotation, params);

	return newProjectile != nullptr ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;  
}