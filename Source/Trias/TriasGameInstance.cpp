// Dactyl Games, all rights reserved.

#include "TriasGameInstance.h"
#include "PlayerC.h"

bool UTriasGameInstance::GetPlayerLookingAt(FHitResult & outHit, float reach, FVector & outLine, ECollisionChannel Channel)
{
	UWorld* World = GetWorld();
	APawn* Player = World->GetFirstPlayerController()->GetPawn();

	FVector OUT PlayerLocation;
	FRotator OUT PlayerRotation;

	World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	FVector LineEnd = PlayerLocation + PlayerRotation.Vector() * reach;
	outLine = LineEnd;
	
	FCollisionQueryParams TraceParams(FName("Name"), false, Player);
	TraceParams.bReturnPhysicalMaterial = true;
	TraceParams.AddIgnoredActor(Player);
	return World->LineTraceSingleByChannel(OUT outHit, PlayerLocation, LineEnd, Channel, TraceParams);
}

void UTriasGameInstance::GiveItem(FString ID)
{
	APlayerC* Player = Cast<APlayerC>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Player->InventoryManager->GiveItem(ID);
}
