// Dactyl Games, all rights reserved.

#include "PlayerC.h"

#define OUT

APlayerC::APlayerC()
{
	PrimaryActorTick.bCanEverTick = true;
	if(!BuildingManager) BuildingManager = CreateDefaultSubobject<UBuildingManger>(FName("Building Manager"));
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

void APlayerC::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &APlayerC::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerC::MoveRight);
	InputComponent->BindAxis("Turn", this, &APlayerC::Turn);
	InputComponent->BindAxis("LookUp", this, &APlayerC::LookUp);
	InputComponent->BindAxis("SlideItem", this, &APlayerC::SlideItem);
	InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerC::InteractWith);
	InputComponent->BindAction("FirstAction", IE_Pressed, this, &APlayerC::UseItem);
	InputComponent->BindAction("SecondAction", IE_Pressed, this, &APlayerC::AltUseItem);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerC::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &APlayerC::StopJumping);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerC::Crouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &APlayerC::Crouch);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerC::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &APlayerC::Sprint);
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

void APlayerC::ItemChanged_Implementation(AItem* Item)
{
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

void APlayerC::Crouch()
{
	if (bInVehicle) return;
	if (!bCrouching)
	{
		if (bSprinting)
		{
			UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
			FVector WorldDir = GetActorForwardVector();
			CharacterMovement->AddImpulse(WorldDir, true);
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
	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	if (!bSprinting)
	{
		bSprinting = true;
		CharacterMovement->MaxWalkSpeed = 500;
	}
	else
	{
		bSprinting = false;
		CharacterMovement->MaxWalkSpeed = 300;
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

UBuildingManger* APlayerC::GetBuildingManagerComponent()
{
	return BuildingManager;
}

