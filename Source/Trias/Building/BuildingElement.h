// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "../Interfaces/InteractiveInterface.h"
#include "../Items/Item.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
#include "BuildingElement.generated.h"

class UBuildingManager;

UENUM()
enum class ProjectedElementStatus
{
	Valid,
	NonValid,
	Standing,
	Done
};

UCLASS()
class TRIAS_API ABuildingElement : public AActor, public IInteractiveInterface
{
	GENERATED_BODY()

public:

	ABuildingElement();

	// Status of PE
	ProjectedElementStatus Status = ProjectedElementStatus::Valid;

	FName Name;
	UStaticMeshComponent* MeshComponent;
	
	// Get status of PE
	UFUNCTION(BlueprintCallable)
	ProjectedElementStatus GetStatus();

	UFUNCTION(BlueprintCallable)
	FName GetName();

	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetMesh();

	UFUNCTION(BlueprintCallable)
	void SetMesh(UStaticMesh* Mesh);

	// Findout where object should snap to
	virtual FVector ReallocateElementToSocket(FHitResult Hit);

	// Interact basing on status
	virtual void Interact_Implementation() override;

	// Get Material
	UFUNCTION(BlueprintCallable)
	virtual void GiveMaterial(AItem* Item);

	UFUNCTION(BlueprintCallable)
	void SetupSocketCollision();
};
