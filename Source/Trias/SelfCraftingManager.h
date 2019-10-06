// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TriasGameState.h"
#include "GameplayTagContainer.h"
#include "SelfCraftingManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIAS_API USelfCraftingManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USelfCraftingManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = GameState)
	ATriasGameState* TGS = nullptr;

	UFUNCTION(BlueprintCallable)
	bool FindItem(TArray<AItem*> Materials, TSubclassOf<AItem> & outFoundItem);
};