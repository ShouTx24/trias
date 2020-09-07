// Dactyl Games, all rights reserved.


#include "SkillManager.h"

// Sets default values for this component's properties
USkillManager::USkillManager()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void USkillManager::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void USkillManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

int USkillManager::GetCondition()
{
	return Condition;
}

int USkillManager::GetStrength()
{
	return Strength;
}

int USkillManager::GetArchery()
{
	return Archery;
}

int USkillManager::GetShooting()
{
	return Shooting;
}

int USkillManager::GetSneak()
{
	return Sneak;
}

int USkillManager::GetCooking()
{
	return Cooking;
}

void USkillManager::ProgressCondition(int Progress)
{
	Condition += Progress;
}

void USkillManager::ProgressStrength(int Progress)
{
	Strength += Progress;
}

void USkillManager::ProgressArchery(int Progress)
{
	Archery += Progress;
}

void USkillManager::ProgressShooting(int Progress)
{
	Shooting += Progress;
}

void USkillManager::ProgressSneak(int Progress)
{
	Sneak += Progress;
}

void USkillManager::ProgressCooking(int Progress)
{
	Cooking += Progress;
}
