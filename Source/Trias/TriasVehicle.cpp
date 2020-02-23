// Dactyl Games, all rights reserved.


#include "TriasVehicle.h"
#include "PlayerC.h"

// Sets default values
ATriasVehicle::ATriasVehicle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATriasVehicle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriasVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriasVehicle::Interact_Implementation()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APlayerC* Player = Cast<APlayerC>(PlayerController->AcknowledgedPawn);
	Sit(PlayerController, Player->bInVehicle);
}

void ATriasVehicle::MoveForward_Implementation(float AxisValue)
{
}

void ATriasVehicle::MoveRight_Implementation(float AxisValue)
{
}

void ATriasVehicle::Turn(float)
{
}

void ATriasVehicle::Sit(APlayerController* PlayerController, bool InVehicle)
{
	if (!InVehicle) EnterVehicle(PlayerController);
	else LeaveVehicle(PlayerController);
}

void ATriasVehicle::EnterVehicle(APlayerController* PlayerController)
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

void ATriasVehicle::LeaveVehicle(APlayerController* PlayerController)
{
	GLog->Log("Leaving Vehicle.");
	APlayerC* Player = Cast<APlayerC>(PlayerController->AcknowledgedPawn);
	Player->Vehicle = nullptr;
	Player->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Player->SetActorEnableCollision(true);
	Player->bInVehicle = false;
	Player->SetActorLocation(this->GetActorLocation());
}


