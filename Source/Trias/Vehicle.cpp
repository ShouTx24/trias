// Dactyl Games, all rights reserved.


#include "Vehicle.h"

// Sets default values
AVehicle::AVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVehicle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &AVehicle::MoveForward);

}

void AVehicle::Interact_Implementation()
{
	GLog->Log("Pawn Change");
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->AcknowledgedPawn->AttachToActor(this,FAttachmentTransformRules::KeepWorldTransform);
	PlayerController->UnPossess();
	PlayerController->SetPawn(this);
}

void AVehicle::MoveForward(float AxisValue)
{
	auto WorldDir = GetActorForwardVector();
	AddMovementInput(WorldDir, AxisValue, false);
}

