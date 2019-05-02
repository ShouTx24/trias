// Trias Development Team, all rights reserved.

#include "TriasGameInstance.h"

bool UTriasGameInstance::GetPlayerLookingAt(FHitResult & outHit, float reach)
{
	UWorld* World = GetWorld();
	APawn* Player = World->GetFirstPlayerController()->GetPawn();

	FVector OUT PlayerLocation;
	FRotator OUT PlayerRotation;

	World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	FVector LineEnd = PlayerLocation + PlayerRotation.Vector() * reach;

	FCollisionQueryParams TraceParams(FName("Name"), false, Player);
	TraceParams.bReturnPhysicalMaterial = true;
	TraceParams.AddIgnoredActor(Player);
	return World->LineTraceSingleByChannel(OUT outHit, PlayerLocation, LineEnd, ECC_WorldStatic, TraceParams);
}

void UTriasGameInstance::TestFun()
{
	GLog->Log("Fine, very fine");
}