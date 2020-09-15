// Dactyl Games, all rights reserved.


#include "BuildingElement.h"
#include "PlayerC.h"
#include "UObject/ConstructorHelpers.h"

ABuildingElement::ABuildingElement()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Meshes/Placeholders/Placeholder_groundplatform.Placeholder_groundplatform'"));
	Name = FName("TestPE");
	MeshPtr = MeshAsset.Object;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	MeshComponent->SetStaticMesh(MeshPtr);
	MeshComponent->SetCollisionProfileName(FName("NoCollision"));
	RootComponent = MeshComponent;
	for (int i = 0; i < 4; i++)
	{
		FString ID = FString::FromInt(i);
		FName SocketID(ID);
		USphereComponent* Collision = CreateDefaultSubobject<USphereComponent>(SocketID);
		Collision->InitSphereRadius(75);
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Collision->SetCollisionProfileName(FName("NoCollision"));
		Collision->AttachTo(MeshComponent, SocketID);
	}
	//	MeshCMP->AttachTo(RootComponent);
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
	return MeshPtr;
}

void ABuildingElement::SetMesh(UStaticMesh* Mesh)
{
	MeshPtr = Mesh;
	MeshComponent->SetStaticMesh(MeshPtr);
}

FVector ABuildingElement::ReallocateElementToSocket(FHitResult Hit)
{
	FVector Allocate = Hit.GetActor()->GetActorLocation();
	Allocate -= Hit.GetComponent()->GetComponentLocation();
	Allocate.Z += 200;
	GLog->Log(Allocate.ToString());
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
