// Dactyl Games, all rights reserved.


#include "ProjectElement.h"
#include "PlayerC.h"
#include "UObject/ConstructorHelpers.h"

AProjectElement::AProjectElement()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Models/Placeholders/Placeholder_groundplatform.Placeholder_groundplatform'"));
	Name = FName("TestPE");
	MeshPtr = MeshAsset.Object;
	UStaticMeshComponent* MeshCMP = CreateDefaultSubobject<UStaticMeshComponent>(FName("Test"));
	MeshCMP->AttachTo(RootComponent);
	MeshCMP->SetStaticMesh(MeshPtr);
	Status = AvailableStand;
}
ProjectElementStatus AProjectElement::GetPE_Status()
{
	return Status;
}

FName AProjectElement::GetPE_Name()
{
	return Name;
}

UStaticMesh* AProjectElement::GetPE_Mesh()
{
	return MeshPtr;
}

void AProjectElement::Interact()
{
	GLog->Log("Test");
	APlayerC* Player = nullptr;
	Player = Cast<APlayerC>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	switch (Status)
	{
		case AvailableStand:
		{
			Player->GetBuildingManagerComponent()->PlaceElement();
			GLog->Log("AvaibleStand");
			break;
		}
		case NonAvailableStand:
		{
			GLog->Log("NonAvaibleStand");
			break;
		}
		case Stand:
		{
			GLog->Log("Stand");
			break;
		}
		default:
		{
			GLog->Log("default");
			break;
		}
	}
}

void AProjectElement::GiveMaterial(AItem*)
{
	;
}
