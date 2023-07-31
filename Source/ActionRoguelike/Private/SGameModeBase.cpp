#include "SGameModeBase.h"

#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

ASGameModeBase::ASGameModeBase()
{
	SpawnTimerInterval = 10;
	MaxBotCount = 10;
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ASGameModeBase::SpawnBotTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* queryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	
	if (ensure(queryInstance))
	{
		queryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryCompleted);
	}
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,EEnvQueryStatus::Type QueryStatus)
{
	
	if (QueryStatus == EEnvQueryStatus::Failed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS query failed!"));
		return;
	}

	int32 numberOfAliveBots = 0;
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* bot = *It;

		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(bot->GetComponentByClass(USAttributeComponent::StaticClass()));
		
		if (AttributeComponent != nullptr && AttributeComponent->IsAlive())
			numberOfAliveBots++;
	}

	if (DifficultyCurve != nullptr)
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	
	
	if (numberOfAliveBots >= MaxBotCount)
		return;
	
	TArray<FVector> locations = QueryInstance->GetResultsAsLocations();

	if (locations.Num() <= 0 )
		return;

	GetWorld()->SpawnActor<AActor>(MinionClass, locations[0], FRotator::ZeroRotator);
}


