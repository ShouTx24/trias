// Dactyl Games, all rights reserved.


#include "TimeManager.h"

// Sets default values for this component's properties
UTimeManager::UTimeManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UTimeManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTimeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UTimeManager::GetInGameTime()
{
	return InGameTime;
}

void UTimeManager::SetInGameTime(float NewTime)
{
	InGameTime = NewTime;
}

void UTimeManager::AddInGameTime(float AddedTime)
{
	if (!bInGameTimeRunning) return;
	if (InGameTime >= 360) InGameTime = 0;
	InGameTime += AddedTime;
}

bool UTimeManager::IsTimeRunning()
{
	return bInGameTimeRunning;
}

void UTimeManager::SetTimeRunning(bool NewState)
{
	bInGameTimeRunning = NewState;
}

float UTimeManager::GetHour()
{
	return InGameTime / 15;
}

