#include "SInteractionComponent.h"

#include "SGameplayInterface.h"

static TAutoConsoleVariable<bool> CVarDrawDebugs(TEXT("ar.DrawDebugs"), false,
	TEXT("Global value for drawing debugs"), ECVF_Cheat);

USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_interactionDistance = 300;
}

void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* pawn = Cast<APawn>(GetOwner());
	
	if( !pawn->IsLocallyControlled() )
		return;
	
	FindBestInteractable();
}

bool USInteractionComponent::CrateInteractionWidget()
{
	DefaultWidgetInstance = CreateWidget<USWorldUserWidget>(GetWorld(), DefaultWidgetClass);
	DefaultWidgetInstance->AttachedActor = FocusedActor;
	_previousFocusedActor = FocusedActor;
	
	if (DefaultWidgetInstance->IsInViewport())
		return true;
		
	DefaultWidgetInstance->AddToViewport();
	return false;
}

void USInteractionComponent::FindBestInteractable()
{
	FCollisionObjectQueryParams objectParameters;
	objectParameters.AddObjectTypesToQuery(ECC_WorldDynamic);
	FCollisionShape collisionShape;
	float radius = 30.0f;
	
	collisionShape.SetSphere(radius);

	AActor* player = GetOwner(); // get's the owner of component
	
	TArray<FHitResult> hits;
	
	FVector eyeLocation;
	FRotator eyeRotation;

	player->GetActorEyesViewPoint(eyeLocation, eyeRotation);
	
	FVector end = eyeLocation + (eyeRotation.Vector() * _interactionDistance);
	
	GetWorld()->SweepMultiByObjectType(
		hits,
		eyeLocation,
		end,
		FQuat::Identity,
		objectParameters,
		collisionShape);

	if(CVarDrawDebugs.GetValueOnGameThread())
		DrawDebugLine(GetWorld(), eyeLocation, end, FColor::Red, false, 2.0f, 0, 2.0f);

	FocusedActor = nullptr;
	
	for (FHitResult hit : hits)
	{
		AActor* hitActor = hit.GetActor();
		
		if(CVarDrawDebugs.GetValueOnGameThread())
			DrawDebugSphere(GetWorld(), hit.ImpactPoint, radius, 32, FColor::Red, false, 2.0f);
	
		if(hitActor == nullptr)
			continue;
		
		if(!hitActor->Implements<USGameplayInterface>())
			continue;

		FocusedActor = hitActor;
		break;
	}

	if (!ensure(DefaultWidgetClass))
		return;

	if (FocusedActor != nullptr)
	{
		if (DefaultWidgetInstance != nullptr)
		{
			// actor has changed but widget instance is not null
			if (FocusedActor != _previousFocusedActor)
			{
				DefaultWidgetInstance->RemoveFromParent();
				DefaultWidgetInstance = nullptr;

				CrateInteractionWidget();
			}
			return;
		}
		
		CrateInteractionWidget();
	}
	else
	{
		if (DefaultWidgetInstance == nullptr)
			return;

		DefaultWidgetInstance->RemoveFromParent();
		DefaultWidgetInstance = nullptr;
	}
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams objectParameters;
	objectParameters.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* player = GetOwner(); // get's the owner of component
	
	FVector eyeLocation;
	FRotator eyeRotation;

	player->GetActorEyesViewPoint(eyeLocation, eyeRotation);

	_interactionDistance = 500;
	FVector end = eyeLocation + (eyeRotation.Vector() * _interactionDistance);
	
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(hit, eyeLocation, end, objectParameters); //RAY TRACING;

	AActor* hitActor = hit.GetActor();

	if(CVarDrawDebugs.GetValueOnGameThread())
		DrawDebugLine(GetWorld(), eyeLocation, end, FColor::Red, false, 2.0f, 0, 2.0f);
	
	if(hitActor == nullptr)
		return;
	
	
	if(!hitActor->Implements<USGameplayInterface>())
		return;
		
	APawn* playerPawn = Cast<APawn>(player);
	ISGameplayInterface::Execute_Interact(hitActor, playerPawn);
}

void USInteractionComponent::SecondInteract()
{
	ServerInteract(FocusedActor);
}

void USInteractionComponent::ServerInteract_Implementation(AActor* inFocus)
{
	if (inFocus == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "No focused actor");
		return;
	}
	
	APawn* playerPawn = Cast<APawn>(GetOwner());
	ISGameplayInterface::Execute_Interact(inFocus, playerPawn);
}

