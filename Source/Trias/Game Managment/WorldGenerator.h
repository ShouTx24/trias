// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DrawDebugHelpers.h"
#include "TriasGameState.h"
#include "GameplayTagContainer.h"
#include "Engine/World.h"
//#include "VoxelWorld.h"
#include "WorldGenerator.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRIAS_API UWorldGenerator : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int WorldSize = 5;
	UPROPERTY(EditAnywhere)
	int BiomeHexRadius = 20;
	UPROPERTY(EditAnywhere)
	float InnerHexRadius = 1000.f;
	//UPROPERTY(EditAnywhere)
	//AVoxelWorld* VoxelWorld = nullptr;

	UFUNCTION(BlueprintCallable)
	void Generate();
	UFUNCTION()
	void SetMiddleMarker(FVector Location);
	UFUNCTION()
	void DrawHexEdge(FVector Center);
};
