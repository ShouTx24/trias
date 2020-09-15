// Dactyl Games, all rights reserved.


#include "Wall.h"
AWall::AWall()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Meshes/Placeholders/Placeholder_Wall.Placeholder_Wall'"));
	Name = FName("TestWall");
	MeshPtr = MeshAsset.Object;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("WallStaticMesh"));
	MeshComponent->SetStaticMesh(MeshPtr);
	MeshComponent->SetCollisionProfileName(FName("NoCollision"));
	RootComponent = MeshComponent;
	//	MeshCMP->AttachTo(RootComponent);
	Status = ProjectedElementStatus::Valid;
}
FVector AWall::ReallocateElementToSocket(FHitResult Hit)
{
	FVector Allocate = Hit.GetActor()->GetActorLocation();
	Allocate -= Hit.GetComponent()->GetComponentLocation();
	Allocate.Z += 200;
	GLog->Log("Wall Alocation");
	return Allocate;
}
