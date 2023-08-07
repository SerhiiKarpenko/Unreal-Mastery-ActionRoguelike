#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SGameplayFunctionLibrary.generated.h"

UCLASS()
class ACTIONROGUELIKE_API USGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool ApplyDamage(AActor* damageCauser, AActor* targetActor, float damageAmount);

	UFUNCTION(BlueprintCallable, Category = "Gameplay") // last parameter is const because then it will be input pin in blueprints.
	static bool ApplyDirectionalDamage(AActor* damageCauser, AActor* targetActor, float damageAmount, const FHitResult &hitResult);
};
