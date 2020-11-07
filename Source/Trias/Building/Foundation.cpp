// Dactyl Games, all rights reserved.


#include "Foundation.h"

AFoundation::AFoundation()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Building/Placeholder_groundplatform.Placeholder_groundplatform'"));
	MeshComponent->SetStaticMesh(MeshAsset.Object);
	SetupSocketCollision();
}

FVector AFoundation::ReallocateElementToSocket(FHitResult Hit)
{
	FVector Allocate = Hit.GetActor()->GetActorLocation();
	Allocate -= Hit.GetComponent()->GetComponentLocation();
	this->SetActorRotation(Hit.GetActor()->GetActorRotation());
	Allocate.Z += 200;
	return Allocate;
}
