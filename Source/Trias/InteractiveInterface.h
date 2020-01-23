// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractiveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRIAS_API IInteractiveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface")
	void Interact();
};
