// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "InventoryManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIAS_API UInventoryManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Inventory)
	TArray<class AItem*>Inventory;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	int ActiveItemIndex = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Inventory)
	int FastbarSize = 5;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Inventory)
	int InventorySize = 15;

	UFUNCTION()
	TArray<class AItem*>GetInventory();

	UFUNCTION()
	AItem* GetItem(AItem* ItemToFind);
	
	UFUNCTION(BlueprintCallable)
	void GiveItem(FString ID);

	UFUNCTION(BlueprintCallable)
	bool PickUpItem(AItem* ItemToPick);

	UFUNCTION(BlueprintCallable)
	void DropItem(int32 ItemToDrop);
	
	UFUNCTION()
	void ValidateItemIndex();
	
	UFUNCTION(BlueprintCallable)
	int GetActiveItemIndex();

};
