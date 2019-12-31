// Dactyl Games, all rights reserved.


#include "ProjectElement.h"
#include "UObject/ConstructorHelpers.h"

AProjectElement::AProjectElement()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Models/Items/TacticalAxe/AxeTactical_3D.AxeTactical_3D'"));
	Name = FName("TestPE");
	MeshPtr = MeshAsset.Object;
	UStaticMeshComponent* MeshCMP = CreateDefaultSubobject<UStaticMeshComponent>(FName("Test"));
	MeshCMP->AttachTo(RootComponent);
	MeshCMP->SetStaticMesh(MeshPtr);
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
}

void AProjectElement::GiveMaterial(AItem*)
{
	;
}
