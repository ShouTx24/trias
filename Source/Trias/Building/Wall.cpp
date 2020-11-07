// Dactyl Games, all rights reserved.


#include "Wall.h"
AWall::AWall()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Building/Placeholder_Wall.Placeholder_Wall'"));
	MeshComponent->SetStaticMesh(MeshAsset.Object);
	SetupSocketCollision();
}
FVector AWall::ReallocateElementToSocket(FHitResult Hit)
{
	FVector Allocate(0, 0, -150);
	FVector Result = Hit.GetComponent()->GetComponentLocation();
	Result.Z -= 100;
	Result -= Hit.GetComponent()->GetOwner()->GetActorLocation();
	this->SetActorRotation(Result.Rotation());
	return Allocate;
}
