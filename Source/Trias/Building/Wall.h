// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Building/BuildingElement.h"
#include "Wall.generated.h"

/**
 * 
 */
UCLASS()
class TRIAS_API AWall : public ABuildingElement
{
	GENERATED_BODY()
public:
	AWall();
	virtual FVector ReallocateElementToSocket(FHitResult Hit) override;
};
