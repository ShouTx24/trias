// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/Classes/Engine/EngineTypes.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "TriasGameInstance.generated.h"

 // Forward Declarations
class APlayerC;

UCLASS()
class TRIAS_API UTriasGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	bool GetPlayerLookingAt(FHitResult & outHit, float reach, FVector & outLine, ECollisionChannel Channel = ECC_WorldStatic);

	UFUNCTION(Exec)
	void GiveItem(FString ID);
};
