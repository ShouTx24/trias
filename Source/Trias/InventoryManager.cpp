// Dactyl Games, all rights reserved.


#include "InventoryManager.h"

// Sets default values for this component's properties
UInventoryManager::UInventoryManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInventoryManager::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UInventoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInventoryManager::PickUpItem(AItem* ItemToPick)
{
	auto& NewItem = ItemToPick;
	Fastbar.Add(NewItem);
	return false;
}

void UInventoryManager::DropItem(AItem* ItemToDrop)
{
	UWorld* World = GetWorld();
}

void UInventoryManager::ValidateItemIndex()
{	
	if (ActiveItemIndex > FastbarSize - 1)
	{
		ActiveItemIndex = 0;
	}
	else if (ActiveItemIndex < 0)
	{
		ActiveItemIndex = FastbarSize - 1;
	}
}

int UInventoryManager::GetActiveItemIndex()
{
	return ActiveItemIndex;
}

