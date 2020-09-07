// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Tools.generated.h"

/**
 * 
 */
UCLASS()
class TRIAS_API ATools : public AItem
{
public:
	GENERATED_BODY()
	virtual void Use() override;
	virtual void AltUse() override;
};
