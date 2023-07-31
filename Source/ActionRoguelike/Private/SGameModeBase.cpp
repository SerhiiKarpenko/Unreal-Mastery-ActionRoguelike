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
	int32 numberOfAliveBots = 0;
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* bot = *It;

		USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttribute(bot);
		
		if (AttributeComponent != nullptr && AttributeComponent->IsAlive())
			numberOfAliveBots++;
	}

	UE_LOG(LogTemp, Log, TEXT("Amount of alive bots %d"), numberOfAliveBots );
	
	if (DifficultyCurve != nullptr)
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	
	
	if (numberOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("Cannot spawn bot, amount of bot's reached maximum"));
		return;
	}
	
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
	
	DrawDebugSphere(GetWorld(), locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
}


