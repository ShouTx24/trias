// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "InteractiveInterface.h"
#include "Engine/World.h"
#include "TriasVehicle.generated.h"

UCLASS()
class TRIAS_API ATriasVehicle : public AActor, public IInteractiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriasVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void MoveForward(float AxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void MoveRight(float AxisValue);

	virtual void Turn(float);

	virtual void Sit(APlayerController* PlayerController, bool InVehicle);
	virtual void EnterVehicle(APlayerController* PlayerController);
	virtual void LeaveVehicle(APlayerController* PlayerController);
};
