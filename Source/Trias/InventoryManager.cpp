// Dactyl Games, all rights reserved.


#include "InventoryManager.h"
#include "PlayerC.h"

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
	if (Fastbar.Num() < FastbarSize)
	{
		Fastbar.Add(NewItem);
		Cast<APlayerC>(GetOwner())->ItemChanged(NewItem);
		return true;
	}
	else return false;
}

void UInventoryManager::DropItem(int32 ID)
{
	if (Fastbar.IsValidIndex(ID))
	{
		AItem* ItemToDrop = Fastbar[ID];
		ItemToDrop->Dropped();
		Fastbar.RemoveAt(ID);
	}
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

