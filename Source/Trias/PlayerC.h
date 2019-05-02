// Trias Development Team, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Item.h"
#include "GameFramework/PlayerController.h"
#include "TriasGameInstance.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/Public/DrawDebugHelpers.h"
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

	UTriasGameInstance* TGI = nullptr;

	///Movement
	void MoveForward(float);
	void MoveRight(float);
	void Turn(float);
	void LookUp(float);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Inventory)
	TArray<class AItem*>Fastbar;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Inventory)
	TArray<class AItem*>Inventory;
	
	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	int ActiveItem;
	
	void SlideItem(float AxisValue);
	void InteractWith();
	void PickUpItem(AItem* ItemToPick);
	void UseItem();

};
