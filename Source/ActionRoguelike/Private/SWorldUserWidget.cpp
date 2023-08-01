#include "SWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

void USWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(AttachedActor))
	{
		RemoveFromParent();
		
		UE_LOG(LogTemp, Log, TEXT("AttachedActor no longer valid, removing health widget"))
		return;
	}
	
	FVector2D screenPosition;
	if( !UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation(), screenPosition))
		return;

	float viewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
	screenPosition /= viewportScale;
	if (ParentSizeBox == nullptr)
		return;

	ParentSizeBox->SetRenderTranslation(screenPosition);
}
