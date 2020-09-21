// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Building/BuildingElement.h"
#include "Foundation.generated.h"

/**
 * 
 */
UCLASS()
class TRIAS_API AFoundation : public ABuildingElement
{
	GENERATED_BODY()
	AFoundation();
	virtual FVector ReallocateElementToSocket(FHitResult Hit) override;
};
