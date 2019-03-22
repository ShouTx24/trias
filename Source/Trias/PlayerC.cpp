// Trias Development Team, all rights reserved.

#include "PlayerC.h"

APlayerC::APlayerC()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerC::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerC::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &APlayerC::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerC::MoveRight);
	InputComponent->BindAxis("Turn", this, &APlayerC::Turn);
	InputComponent->BindAxis("LookUp", this, &APlayerC::LookUp);
}

void APlayerC::MoveForward(float AxisValue)
{
	auto WorldDir = GetActorForwardVector();
	AddMovementInput(WorldDir, AxisValue, false);
}

void APlayerC::MoveRight(float AxisValue)
{
	auto WorldDir = GetActorRightVector();
	AddMovementInput(WorldDir, AxisValue, false);
}

void APlayerC::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerC::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

