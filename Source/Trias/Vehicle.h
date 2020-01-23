// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "InteractiveInterface.h"
#include "Engine/World.h"
#include "Vehicle.generated.h"

UCLASS()
class TRIAS_API AVehicle : public APawn, public IInteractiveInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Interact_Implementation() override;

	void MoveForward(float);
};
