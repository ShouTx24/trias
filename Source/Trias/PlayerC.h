// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Items/Item.h"
#include "GameFramework/PlayerController.h"
#include "Game Managment/TriasGameInstance.h"
#include "Game Managment/TriasGameState.h"
#include "Interfaces/InteractiveInterface.h"
#include "Camera/PlayerCameraManager.h"
#include "Managers/BuildingManager.h"
#include "Managers/SkillManager.h"
#include "Managers/InventoryManager.h"
#include "Vehicles/TriasVehicle.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Public/CollisionQueryParams.h"
#include "PlayerC.generated.h"

UCLASS()
class TRIAS_API APlayerC : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerC();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
	UTriasGameInstance* TGI = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ATriasGameState* TGS = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UBuildingManager* BuildingManager = nullptr;

	UPROPERTY(BlueprintReadOnly)
	USkillManager* SkillManager = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UInventoryManager* InventoryManager = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Inventory)
	UStaticMeshComponent* Hand = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	bool bInVehicle = false;

	UPROPERTY(BlueprintReadWrite)
	ATriasVehicle* Vehicle;

	UFUNCTION()
	UBuildingManager* GetBuildingManagerComponent();
	
	////Physiology
	///Health
private:	
	
	UPROPERTY()
	float HealthHead = 100.f;
	
	UPROPERTY()
	float HealthChest = 100.f;
	
	UPROPERTY()
	float HealthStomach = 100.f;
	
	UPROPERTY()
	float HealthArms = 100.f;
	
	UPROPERTY()
	float HealthLegs = 100.f;

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealthHead();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealthChest();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealthStomach();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealthArms();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealthLegs();
	
	///Movement
	UFUNCTION()
	void MoveForward(float AxisValue);
	
	UFUNCTION()
	void MoveRight(float AxisValue);
	
	UFUNCTION()
	void Turn(float AxisValue);
	
	UFUNCTION()
	void LookUp(float AxisValue);

	void Jump();
	void StopJumping();
	
	bool bCrouching = false;
	void TurnCrouching();

	bool bSprinting = false;
	void Sprint();

	UFUNCTION()
	void Slide();
	
	///Equipment & Items
	
	UFUNCTION()
	void SlideItem(float AxisValue);
	
	UFUNCTION()
	void InteractWith();
	
	UFUNCTION()
	void UseItem();
	
	UFUNCTION()
	void AltUseItem();

};