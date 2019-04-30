// Trias Development Team, all rights reserved.

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
		~ATools();
	virtual void Use() override;
};