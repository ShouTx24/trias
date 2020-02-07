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
	APlayerC* Player = Cast<APlayerC>(PlayerController->AcknowledgedPawn);
	Sit(PlayerController, Player->bInVehicle);
}

void AVehicle::MoveForward_Implementation(float AxisValue)
{
}

void AVehicle::MoveRight_Implementation(float AxisValue)
{
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
	FAttachmentTransformRules VehicleTRules(EAttachmentRule::KeepWorld, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	Player->AttachToActor(this, VehicleTRules);
	Player->SetActorEnableCollision(false);
	Player->SetActorLocation(this->GetActorLocation());
	Player->bInVehicle = true;
	Player->Vehicle = this;
}

void AVehicle::LeaveVehicle(APlayerController* PlayerController)
{
	GLog->Log("Leaving Vehicle.");
	APlayerC* Player = Cast<APlayerC>(PlayerController->AcknowledgedPawn);
	Player->Vehicle = nullptr;
	Player->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Player->SetActorEnableCollision(true);
	Player->bInVehicle = false;
	Player->SetActorLocation(this->GetActorLocation());
}

