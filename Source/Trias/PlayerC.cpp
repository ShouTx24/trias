// Trias Development Team, all rights reserved.

#include "PlayerC.h"
#include "Item.h"

#define OUT

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
	InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerC::InteractWith);
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

void APlayerC::InteractWith()
{
	FHitResult Hit;
	GetPlayerLookingAt(OUT Hit, 400);
	AActor* HittenActor = Hit.GetActor();
	if (HittenActor)
	{
		if (HittenActor->GetClass()->IsChildOf<AInteractiveObject>())
		{
			AInteractiveObject* Object = Cast<AInteractiveObject>(HittenActor);
			GLog->Log("Item is a " + Object->GetName());
			Object->Interact();
		}
		else GLog->Log("Not a item, beacouse it is " + HittenActor->GetName());
	}
}

bool APlayerC::GetPlayerLookingAt(FHitResult & outHit, float reach)
{
	UWorld* World = GetWorld();
	APawn* Player = World->GetFirstPlayerController()->GetPawn();
	
	FVector OUT PlayerLocation;
	FRotator OUT PlayerRotation;
	
	World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	FVector LineEnd = PlayerLocation + PlayerRotation.Vector() * reach;

	FCollisionQueryParams TraceParams(FName("Name"), false, this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;
	TraceParams.AddIgnoredActor(Player);
	
	return World->LineTraceSingleByChannel(outHit, PlayerLocation, LineEnd, ECC_WorldStatic, TraceParams);
}

