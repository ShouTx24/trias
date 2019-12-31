// Dactyl Games, all rights reserved.


#include "BuildingManger.h"

// Sets default values for this component's properties
UBuildingManger::UBuildingManger()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuildingManger::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UBuildingManger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

AProjectElement* UBuildingManger::SpawnElement()
{
//	AProjectElement* PE;
	
	UWorld* World = GetWorld();
	if (!World) return nullptr;

	UClass* PEC = AProjectElement::StaticClass();
	
	World->SpawnActor<AProjectElement>();

	return nullptr;
}

