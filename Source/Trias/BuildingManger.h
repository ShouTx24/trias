// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectElement.h"
#include "TriasGameInstance.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "BuildingManger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIAS_API UBuildingManger : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingManger();

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
	AProjectElement* SpawnElement();

	void GrabElement(AProjectElement* PE);

	// Place project element.
	bool PlaceElement();
	// Give project element a material.

	// Materialised project element.
};
