// Trias Development Team, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/Classes/Engine/EngineTypes.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "TriasGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TRIAS_API UTriasGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	bool GetPlayerLookingAt(FHitResult & outHit, float reach);
};
