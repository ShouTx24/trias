// Dactyl Games, all rights reserved.


#include "SelfCraftingManager.h"

// Sets default values for this component's properties
USelfCraftingManager::USelfCraftingManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USelfCraftingManager::BeginPlay()
{
	Super::BeginPlay();

	TGS = GetWorld()->GetGameState<ATriasGameState>();
}


// Called every frame
void USelfCraftingManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USelfCraftingManager::FindItem(TArray<AItem*> Materials, OUT TSubclassOf<AItem> &outFoundItem)
{
	if (TGS)
	{
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
				OUT outFoundItem = ItemClass;
				return true;
			}
		}

		return false;
	}
	
	else
	{
		GLog->Log("Error: Game State is not set");
		return false;
	}

}

