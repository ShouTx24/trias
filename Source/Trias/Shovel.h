// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tools.h"
#include "TriasGameInstance.h"
#include "VoxelTools/VoxelSphereTools.h"
#include "VoxelWorld.h"
#include "Shovel.generated.h"

/**
 * 
 */
UCLASS()
class TRIAS_API AShovel : public ATools
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Use() override;
	virtual void AltUse() override;

	UTriasGameInstance* TGI = nullptr;
	
	AVoxelWorld* VoxelWorld = nullptr;
};
