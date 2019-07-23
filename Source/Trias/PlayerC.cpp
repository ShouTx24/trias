// Trias Development Team, all rights reserved.

#include "PlayerC.h"

#define OUT

APlayerC::APlayerC()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerC::BeginPlay()
{
	Super::BeginPlay();
	ActiveItem = Fastbar.Num() - 1;
	TGI = Cast<UTriasGameInstance>(GetGameInstance());
	if (TGI)
	{
		GLog->Log("Fine!");
	}
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
	InputComponent->BindAxis("Slide", this, &APlayerC::SlideItem);
	InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerC::InteractWith);
	InputComponent->BindAction("FirstAction", IE_Pressed, this, &APlayerC::UseItem);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

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

void APlayerC::SlideItem(float AxisValue)
{
	if(Fastbar.Num() > 0) ActiveItem += AxisValue;
	if (ActiveItem > Fastbar.Num() - 1)
	{
		ActiveItem = 0;
	}
	else if (ActiveItem < 0)
	{
		ActiveItem = Fastbar.Num() - 1;
	}
}

void APlayerC::InteractWith()
{
	FHitResult Hit;
	if (TGI)
	{
		if (TGI->GetPlayerLookingAt(OUT Hit, 400))
		{
			AActor* HittenActor = Hit.GetActor();
			if (HittenActor->GetClass()->IsChildOf<AInteractiveObject>())
			{
				AInteractiveObject* Object = Cast<AInteractiveObject>(HittenActor);

				GLog->Log("Item: " + Object->GetName());

				if (Object->GetClass()->IsChildOf<AItem>())
				{
					AItem* NewItem = Cast<AItem>(Object);
					PickUpItem(NewItem);
				}
				Object->Interact();
			}
		}
	}
}

void APlayerC::PickUpItem(AItem* NewIte)
{
	auto &NewItem = NewIte;
	Fastbar.Add(NewItem);
}

void APlayerC::UseItem()
{
	if (Fastbar.Num()-1 >= 0 && Fastbar.IsValidIndex(ActiveItem))
	{
		Fastbar[ActiveItem]->Use();
	}
}

