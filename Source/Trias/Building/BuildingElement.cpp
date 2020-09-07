// Dactyl Games, all rights reserved.


#include "BuildingElement.h"
#include "PlayerC.h"
#include "UObject/ConstructorHelpers.h"

ABuildingElement::ABuildingElement()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Meshes/Placeholders/Placeholder_groundplatform.Placeholder_groundplatform'"));
	Name = FName("TestPE");
	MeshPtr = MeshAsset.Object;
	UStaticMeshComponent* MeshCMP = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	MeshCMP->SetStaticMesh(MeshPtr);
	MeshCMP->SetCollisionProfileName(FName("NoCollision"));
	RootComponent = MeshCMP;
	for (int i = 0; i < 4; i++)
	{
		FString ID = FString::FromInt(i);
		FName SocketID(ID);
		USphereComponent* Collision = CreateDefaultSubobject<USphereComponent>(SocketID);
		Collision->InitSphereRadius(75);
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Collision->SetCollisionProfileName(FName("NoCollision"));
		Collision->AttachTo(MeshCMP, SocketID);
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

void ABuildingElement::Interact_Implementation()
{
	APlayerC* Player = nullptr;
	Player = Cast<APlayerC>(GetWorld()->GetFirstPlayerController()->GetPawn());

	switch (Status)
	{
	case ProjectedElementStatus::Valid:
	{
		Player->GetBuildingManagerComponent()->PlaceElement();
		GLog->Log("Valid");
		break;
	}
	case ProjectedElementStatus::NonValid:
	{
		GLog->Log("NonValid");
		break;
	}
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
