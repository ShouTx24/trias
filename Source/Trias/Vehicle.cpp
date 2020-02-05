// Dactyl Games, all rights reserved.


#include "Vehicle.h"
#include "PlayerC.h"

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

void AVehicle::Interact_Implementation()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	Sit(PlayerController, false);
}

void AVehicle::MoveForward(float AxisValue)
{
	GLog->Log("Moving Forward");
}

void AVehicle::MoveRight(float AxisValue)
{
	GLog->Log("Turning");
}

void AVehicle::Turn(float)
{
}

void AVehicle::Sit(APlayerController* PlayerController, bool InVehicle)
{
	if (!InVehicle) EnterVehicle(PlayerController);
	else LeaveVehicle(PlayerController);
}

void AVehicle::EnterVehicle(APlayerController* PlayerController)
{
	GLog->Log("Entering Vehicle.");
	APlayerC* Player = Cast<APlayerC>(PlayerController->AcknowledgedPawn);
	Player->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	Player->SetActorEnableCollision(false);
	Player->SetActorLocation(this->GetActorLocation());
	Player->Vehicle = this;
}

void AVehicle::LeaveVehicle(APlayerController* PlayerController)
{
	GLog->Log("Leaving Vehicle.");
	PlayerController->AcknowledgedPawn->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	PlayerController->AcknowledgedPawn->SetActorEnableCollision(true);
	PlayerController->AcknowledgedPawn->SetActorLocation(this->GetActorLocation());
}

