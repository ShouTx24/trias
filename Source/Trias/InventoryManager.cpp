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
	TGS = GetWorld()->GetGameState<ATriasGameState>();
}


// Called every frame
void UInventoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

TArray<class AItem*> UInventoryManager::GetInventory()
{
	return Inventory;
}

AItem* UInventoryManager::GetItem(AItem* ItemToFind)
{
	return nullptr;
}

void UInventoryManager::GiveItem(FString ID)
{
	ATriasGameState* TGS = Cast<ATriasGameState>(GetWorld()->GetGameState());
	for (TSubclassOf<AItem> ItemClass : TGS->ItemList)
	{
		AItem* Item = Cast<AItem>(ItemClass->GetDefaultObject());
		if (Item->ID == ID) 
		{ 
			if (Inventory.Num() < FastbarSize)
			{
//				Inventory.Add(Item);
				Item = Cast<AItem>(GetWorld()->SpawnActor(Item->GetClass()));
				PickUpItem(Item);
				Item->PickedUp();
//				Cast<APlayerC>(GetOwner())->ItemChanged(Item);
			}
		}
		else GLog->Log("Item not found!");
		
	}
}

bool UInventoryManager::PickUpItem(AItem* ItemToPick)
{
	auto& NewItem = ItemToPick;
	if (Inventory.Num() < FastbarSize)
	{
		Inventory.Add(NewItem);
//		Cast<APlayerC>(GetOwner())->ItemChanged(NewItem);
		return true;
	}
	else return false;
}

void UInventoryManager::DropItem(int32 ID)
{
	if (Inventory.IsValidIndex(ID))
	{
		AItem* ItemToDrop = Inventory[ID];
		ItemToDrop->Dropped();
		Inventory.RemoveAt(ID);
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

bool UInventoryManager::FindItem(TArray<AItem*> Materials, TSubclassOf<AItem>& outFoundItem, FString& NewItemID)
{
	if (!TGS) return false;
	if (Materials.Num() <= 0) return false;
	TArray<FString> IDs;
	for (AItem* Item : Materials)
	{
		IDs.Add(Item->ID);
	}
	for (TSubclassOf<AItem> ItemClass : TGS->ItemList)
	{
		AItem* Item = Cast<AItem>(ItemClass->GetDefaultObject());

		Item->Recipe.StableSort();
		IDs.StableSort();

		if (Item->Recipe == IDs)
		{
			outFoundItem = ItemClass;
			NewItemID = Item->ID;
			return true;
		}
	}
	return false;
}