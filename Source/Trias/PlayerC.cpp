// Dactyl Games, all rights reserved.

#include "PlayerC.h"

#define OUT

APlayerC::APlayerC()
{
	PrimaryActorTick.bCanEverTick = true;
	if(!BuildingManager) BuildingManager = CreateDefaultSubobject<UBuildingManager>(FName("Building Manager"));
	if(!InventoryManager) InventoryManager = CreateDefaultSubobject<UInventoryManager>(FName("Inventory Manager"));
	if(!SkillManager) SkillManager = CreateDefaultSubobject<USkillManager>(FName("Skill Manager"));
	Hand = CreateDefaultSubobject<UStaticMeshComponent>(FName("PlayerHand"));
	Hand->AttachTo(RootComponent);
}

void APlayerC::BeginPlay()
{
	Super::BeginPlay();
	TGI = Cast<UTriasGameInstance>(GetGameInstance());
	TGS = GetWorld()->GetGameState<ATriasGameState>();
}

void APlayerC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerC::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerC::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerC::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerC::LookUp);
	PlayerInputComponent->BindAxis("SlideItem", this, &APlayerC::SlideItem);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerC::InteractWith);
	PlayerInputComponent->BindAction("FirstAction", IE_Pressed, this, &APlayerC::UseItem);
	PlayerInputComponent->BindAction("SecondAction", IE_Pressed, this, &APlayerC::AltUseItem);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerC::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerC::StopJumping);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerC::TurnCrouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerC::TurnCrouching);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerC::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerC::Sprint);
}

float APlayerC::GetHealthHead()
{
	return HealthHead;
}

float APlayerC::GetHealthChest()
{
	return HealthChest;
}

float APlayerC::GetHealthStomach()
{
	return HealthStomach;
}

float APlayerC::GetHealthArms()
{
	return HealthArms;
}

float APlayerC::GetHealthLegs()
{
	return HealthLegs;
}

void APlayerC::MoveForward(float AxisValue)
{
	if (bInVehicle, Vehicle) Vehicle->MoveForward(AxisValue);
	else
	{
		FVector WorldDir = GetActorForwardVector();
		AddMovementInput(WorldDir, AxisValue, false);
	}
}

void APlayerC::MoveRight(float AxisValue)
{
	if (bInVehicle, Vehicle) Vehicle->MoveRight(AxisValue);
	else 
	{
		FVector WorldDir = GetActorRightVector();
		AddMovementInput(WorldDir, AxisValue, false);
	}
}

void APlayerC::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerC::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayerC::Jump()
{
	if(!bInVehicle) ACharacter::Jump();
}

void APlayerC::StopJumping()
{
	ACharacter::StopJumping();
}

void APlayerC::TurnCrouching()
{
	if (bInVehicle) return;
	if (!bCrouching)
	{
		if (bSprinting)
		{
			UCharacterMovementComponent* CharacterMovementPointer = GetCharacterMovement();
			FVector WorldDir = GetActorForwardVector();
			CharacterMovementPointer->AddImpulse(WorldDir, true);
		}
		ACharacter::Crouch();
		bCrouching = true;
	}
	else
	{
		ACharacter::UnCrouch();
		bCrouching = false;
	}
}

void APlayerC::Sprint()
{
//	if (bInVehicle) return;
	UCharacterMovementComponent* CharacterMovementPointer = GetCharacterMovement();
	if (!bSprinting)
	{
		bSprinting = true;
		CharacterMovementPointer->MaxWalkSpeed = 500;
	}
	else
	{
		bSprinting = false;
		CharacterMovementPointer->MaxWalkSpeed = 300;
	}
}

void APlayerC::Slide()
{
	GLog->Log("Sliding");
}

void APlayerC::SlideItem(float AxisValue)
{
	InventoryManager->ActiveItemIndex -= AxisValue;
	InventoryManager->ValidateItemIndex();
	if (InventoryManager->Inventory.IsValidIndex(InventoryManager->GetActiveItemIndex())) Hand->SetStaticMesh(InventoryManager->Inventory[InventoryManager->GetActiveItemIndex()]->Model);
	else Hand->SetStaticMesh(nullptr);
}

void APlayerC::InteractWith()
{
	FHitResult Hit;
	FVector Line;
	if (TGI)
	{
		if (TGI->GetPlayerLookingAt(OUT Hit, 300, Line))
		{
			AActor* HittenActor = Hit.GetActor();
			IInteractiveInterface* InteractiveComponent = Cast<IInteractiveInterface>(HittenActor);
			if (InteractiveComponent)
			{
				if (Cast<AItem>(HittenActor))
				{
					AItem* NewItem = Cast<AItem>(HittenActor);
					if (InventoryManager->PickUpItem(NewItem)) InteractiveComponent->Execute_Interact(HittenActor);
				}
				else if (InteractiveComponent)
				{
					InteractiveComponent->Execute_Interact(HittenActor);
				}
			}
		}
	}
}

void APlayerC::UseItem()
{
	int ActiveItem = InventoryManager->GetActiveItemIndex();
	if (BuildingManager->PhysicsHandleComponent->GetGrabbedComponent())
	{
		BuildingManager->PlaceElement();
	}
	else if (InventoryManager->Inventory.IsValidIndex(ActiveItem)) InventoryManager->Inventory[ActiveItem]->Use();
	else GLog->Log("Hand Attack!");
}

void APlayerC::AltUseItem()
{
	int ActiveItem = InventoryManager->GetActiveItemIndex();

	if (InventoryManager->Inventory.IsValidIndex(ActiveItem)) InventoryManager->Inventory[ActiveItem]->AltUse();
	else GLog->Log("Block");
}

UBuildingManager* APlayerC::GetBuildingManagerComponent()
{
	return BuildingManager;
}

