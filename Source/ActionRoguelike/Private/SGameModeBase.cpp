#include "SGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

ASGameModeBase::ASGameModeBase()
{
	SpawnTimerInterval = 2;
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
	
	TArray<FVector> locations = QueryInstance->GetResultsAsLocations();

	if (locations.Num() <= 0 )
		return;

	GetWorld()->SpawnActor<AActor>(MinionClass, locations[0], FRotator::ZeroRotator);
}


