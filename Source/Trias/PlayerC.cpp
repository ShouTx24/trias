// Trias Development Team, all rights reserved.

#include "PlayerC.h"

#define OUT

APlayerC::APlayerC()
{
	PrimaryActorTick.bCanEverTick = true;
	if(!CraftingManager) CraftingManager = CreateDefaultSubobject<USelfCraftingManager>(FName("Crafting Manager"));
	if(!BuildingManager) BuildingManager = CreateDefaultSubobject<UBuildingManger>(FName("Building Manager"));
	if(!SkillManager) SkillManager = CreateDefaultSubobject<USkillManager>(FName("Skill Manager"));
	Hand = CreateDefaultSubobject<UStaticMeshComponent>(FName("PlayerHand"));
	Hand->AttachTo(RootComponent);
}

void APlayerC::BeginPlay()
{
	Super::BeginPlay();
	ActiveItem = Fastbar.Num() - 1;
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
	ACharacter::Jump();
}

void APlayerC::StopJumping()
{
	ACharacter::StopJumping();
}

void APlayerC::Crouch()
{
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
	GLog->Log("Sprinting");
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
	if (Fastbar.Num() > 0)
	{
		ActiveItem += AxisValue;
	}
	if (ActiveItem > Fastbar.Num() - 1)
	{
		ActiveItem = 0;
	}
	else if (ActiveItem < 0)
	{
		ActiveItem = Fastbar.Num() - 1;
	}
	if(Fastbar.IsValidIndex(ActiveItem)) Hand->SetStaticMesh(Fastbar[ActiveItem]->Model);
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
				InteractiveComponent->Execute_Interact(HittenActor);
			}
			if (Cast<AItem>(HittenActor))
			{
				AItem* NewItem = Cast<AItem>(HittenActor);
				PickUpItem(NewItem);
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
	else if (BuildingManager->PhysicsHandleComponent->GetGrabbedComponent())
	{
		BuildingManager->PlaceElement();
	}
}

UBuildingManger* APlayerC::GetBuildingManagerComponent()
{
	return BuildingManager;
}

