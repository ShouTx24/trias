// Dactyl Games, all rights reserved.


#include "BuildingElement.h"
#include "PlayerC.h"
#include "UObject/ConstructorHelpers.h"

ABuildingElement::ABuildingElement()
{
	Name = FName("Projected element");
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	MeshComponent->SetCollisionProfileName(FName("NoCollision"));
	RootComponent = MeshComponent;
	Status = ProjectedElementStatus::Valid;
}
ProjectedElementStatus ABuildingElement::GetStatus()
{
	return Status;
}

FName ABuildingElement::GetName()
{
	return Name;
}

UStaticMesh* ABuildingElement::GetMesh()
{
	return MeshComponent->GetStaticMesh();
}

void ABuildingElement::SetMesh(UStaticMesh* Mesh)
{
	MeshComponent->SetStaticMesh(Mesh);
}

FVector ABuildingElement::ReallocateElementToSocket(FHitResult Hit)
{
	FVector Allocate = Hit.GetActor()->GetActorLocation();
	Allocate -= Hit.GetComponent()->GetComponentLocation();
	Allocate.Z += 200;
	return Allocate;
}

void ABuildingElement::Interact_Implementation()
{
	APlayerC* Player = nullptr;
	Player = Cast<APlayerC>(GetWorld()->GetFirstPlayerController()->GetPawn());

	switch (Status)
	{
		case ProjectedElementStatus::Standing:
		{
			GLog->Log("Standing");
			break;
		}
		default:
		{
			GLog->Log("default");
			break;
		}
	}
}

void ABuildingElement::GiveMaterial(AItem*)
{
	;
}

void ABuildingElement::SetupSocketCollision()
{
	for (int i = 0; i < MeshComponent->GetAllSocketNames().Num(); i++)
	{
		FName SocketID(FString::FromInt(i));
		USphereComponent* Collision = CreateDefaultSubobject<USphereComponent>(SocketID);
		Collision->InitSphereRadius(50);
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Collision->SetCollisionProfileName(FName("NoCollision"));
		Collision->AttachTo(MeshComponent, SocketID);
	}
}
