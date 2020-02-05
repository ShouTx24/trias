// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveInterface.h"
#include "Item.h"
#include "Engine/StaticMesh.h"
#include "ProjectElement.generated.h"

/**
 * 
 */

class UBuildingManager;

UENUM()
enum ProjectElementStatus 
{ 
	NonAvailableStand, 
	AvailableStand, 
	Stand, 
	Materialised 
};

UCLASS()
class TRIAS_API AProjectElement : public AActor, public IInteractiveInterface
{	
	GENERATED_BODY()

public:
	
	AProjectElement();
	
	// Status of PE
	ProjectElementStatus Status = NonAvailableStand;
	
	FName Name;
	UStaticMesh* MeshPtr;

	// Get status of PE
	UFUNCTION(BlueprintCallable)
	ProjectElementStatus GetPE_Status();

	UFUNCTION(BlueprintCallable)
	FName GetPE_Name();

	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetPE_Mesh();

	// Interact basing on status
	virtual void Interact_Implementation() override;

	// Get Material
	UFUNCTION(BlueprintCallable)
	virtual void GiveMaterial(AItem* Item);

};