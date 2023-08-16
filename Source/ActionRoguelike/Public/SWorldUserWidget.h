#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "SWorldUserWidget.generated.h"


UCLASS()
class ACTIONROGUELIKE_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector WorldPositionOffset;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (ExposeOnSpawn=true))
	AActor* AttachedActor;
	
protected:

	UPROPERTY(meta = (BindWidget))
	class USizeBox* ParentSizeBox;
	

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
