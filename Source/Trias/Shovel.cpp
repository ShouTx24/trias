// Dactyl Games, all rights reserved.


#include "Shovel.h"

void AShovel::BeginPlay()
{
	Super::BeginPlay();
	TGI = Cast<UTriasGameInstance>(GetGameInstance());
}

void AShovel::Use()
{
	GLog->Log(GetName() + " is in use!");
	FHitResult OUT Hit;
	FVector Line;
	TGI->GetPlayerLookingAt(Hit, 400, Line);
	if (Cast<AVoxelWorld>(Hit.GetActor()))
	{
		VoxelWorld = Cast<AVoxelWorld>(Hit.GetActor());
		UVoxelSphereTools::RemoveSphere(VoxelWorld, Hit.ImpactPoint, 35, true);
		UVoxelSphereTools::SmoothSphere(VoxelWorld, Hit.ImpactPoint, 35 * 1.5, 20, true);
	}
	else return;
}

void AShovel::AltUse()
{
	GLog->Log(GetName() + " is in alt use!");
	FHitResult OUT Hit;
	FVector Line;
	TGI->GetPlayerLookingAt(Hit, 400, Line);
	if (Cast<AVoxelWorld>(Hit.GetActor()))
	{
		VoxelWorld = Cast<AVoxelWorld>(Hit.GetActor());
		UVoxelSphereTools::RemoveSphere(VoxelWorld, Hit.ImpactPoint, 35, true);
		UVoxelSphereTools::SmoothSphere(VoxelWorld, Hit.ImpactPoint, 35 * 1.5, 20, true);
	}
	else return;
}
