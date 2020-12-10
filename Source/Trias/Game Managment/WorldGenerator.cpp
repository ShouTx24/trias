// Dactyl Games, all rights reserved.


#include "WorldGenerator.h"

void UWorldGenerator::Generate()
{
	//if (VoxelWorld) VoxelWorld->CreateWorld();
	FVector StartLocation, ActualLocation = FVector(0.f, 0.f, 0.f);
	int sign = 1;
	for (int y = 0; y < WorldSize; y++)
	{
		for (int x = 0; x < WorldSize / 4; x++)
		{
			ActualLocation += FVector(3 * InnerHexRadius, 0.f, 0.f);
			SetMiddleMarker(ActualLocation);
			DrawHexEdge(ActualLocation);
		}
		sign *= -1;
		StartLocation += FVector(1.5 * InnerHexRadius * sign, InnerHexRadius * 0.866, 0.f);
		ActualLocation = StartLocation;
	}
}

void UWorldGenerator::SetMiddleMarker(FVector Location)
{
	UWorld* World = GetWorld();
	DrawDebugPoint(World, Location, 10.f, FColor::Red, false, 500.f);
}

void UWorldGenerator::DrawHexEdge(FVector Center)
{
	UWorld* World = GetWorld();

	Center += FVector(-InnerHexRadius, 0.f, 0.f);
	FRotator AngleRotation(0.f, -120, 0.f);
	
	for (int i = 0; i < 6; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Center is %s"), *Center.ToString());
		AngleRotation.Add(0.f, 60.f, 0.f);
		FVector LineEnd = Center + AngleRotation.Vector() * InnerHexRadius;
		UE_LOG(LogTemp, Warning, TEXT("End is %s"), *LineEnd.ToString());
		DrawDebugLine(World, Center, LineEnd, FColor::Red, false, 500.f);
		Center = LineEnd;
	}
}
