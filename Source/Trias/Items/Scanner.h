// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tools.h"
#include "../Game Managment/TriasGameInstance.h"
#include "Scanner.generated.h"

/**
 * 
 */
UCLASS()
class TRIAS_API AScanner : public ATools
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Use() override;
	
	UTriasGameInstance* TGI = nullptr;
	
	AActor* Scan();
	
};
