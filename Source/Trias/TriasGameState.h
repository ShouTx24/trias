// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Item.h"
#include "GameplayTagContainer.h"
#include "TriasGameState.generated.h"

/**
 * 
 */
UCLASS()
class TRIAS_API ATriasGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Item)
	TArray< TSubclassOf <class AItem> > ItemList;

	virtual void BeginPlay() override;
};
