// Trias Development Team, all rights reserved.

#include "Scanner.h"

void AScanner::BeginPlay()
{
	Super::BeginPlay();
	TGI = Cast<UTriasGameInstance>(GetGameInstance());
}

void AScanner::Use()
{
	GLog->Log(GetName() + " is in use!");
	GLog->Log(ID.GetTagName().ToString());
	Scan();
}

AActor* AScanner::Scan()
{
	FHitResult OUT Hit;
	TGI->GetPlayerLookingAt(Hit,20000);
	if (Hit.GetActor())
	{
		AActor* ScanActor = Hit.GetActor();
		GLog->Log("This is a " + ScanActor->GetName());
		return ScanActor;
	}
	return nullptr;
}
