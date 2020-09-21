// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Building/BuildingElement.h"
#include "../Game Managment/TriasGameInstance.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/SphereComponent.h"
#include "BuildingManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIAS_API UBuildingManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UTriasGameInstance* TGI = nullptr;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandleComponent;

	// Spawns UI to choose build element & spawn projectile.

	UFUNCTION(BlueprintCallable)
	ABuildingElement* SpawnElement(TSubclassOf<ABuildingElement> Element);

	UClass* ClassPointer;
	
	void GrabElement(ABuildingElement* PE);


	// Place projected element.
	bool PlaceElement();
	// Give projected element a material.

	// Materialised project element.
	
	// Cancel placement
	void CancelPlacement();
};
