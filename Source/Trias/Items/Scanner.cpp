// Dactyl Games, all rights reserved.

#include "Scanner.h"

void AScanner::BeginPlay()
{
	Super::BeginPlay();
	TGI = Cast<UTriasGameInstance>(GetGameInstance());
}

void AScanner::Use()
{
	GLog->Log(GetName() + " is in use!");
	Scan();
}

AActor* AScanner::Scan()
{
	FHitResult OUT Hit;
	FVector Line;
	TGI->GetPlayerLookingAt(Hit,20000, Line);
	if (Hit.GetActor())
	{
		AActor* ScanActor = Hit.GetActor();
		GLog->Log("This is a " + ScanActor->GetName());
		return ScanActor;
	}
	return nullptr;
}
