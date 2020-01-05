// Dactyl Games, all rights reserved.


#include "BuildingManger.h"

// Sets default values for this component's properties
UBuildingManger::UBuildingManger()
{
	PrimaryComponentTick.bCanEverTick = true;
	if (!PhysicsHandleComponent) PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(FName("PhysicsHandleComponent"));

}


// Called when the game starts
void UBuildingManger::BeginPlay()
{
	Super::BeginPlay();
	TGI = Cast<UTriasGameInstance>(GetWorld()->GetGameInstance());
}


// Called every frame
void UBuildingManger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandleComponent->GetGrabbedComponent())
	{
		FHitResult Hit;
		FVector Line;
		TGI->GetPlayerLookingAt(Hit, 450, Line);
		PhysicsHandleComponent->GetGrabbedComponent()->SetWorldLocation(Line);
	}
}

AProjectElement* UBuildingManger::SpawnElement()
{	
	UWorld* World = GetWorld();
	if (!World) return nullptr;

	UClass* PEC = AProjectElement::StaticClass();
	AProjectElement* PE = World->SpawnActor<AProjectElement>();
	PE->SetActorEnableCollision(true);
	GrabElement(PE);
	return PE;
}

void UBuildingManger::GrabElement(AProjectElement* PE)
{
	UPrimitiveComponent* PEP = Cast<UPrimitiveComponent>(PE->GetRootComponent());
	PhysicsHandleComponent->GrabComponentAtLocation	(
														PEP, 
														NAME_None, 
														PE->GetTargetLocation()
													); 
}

bool UBuildingManger::PlaceElement()
{
	if (PhysicsHandleComponent->GetGrabbedComponent())
	{
		GLog->Log("Releasing Object");
		PhysicsHandleComponent->ReleaseComponent();
		return true;
	}
	else
	{
		GLog->Log("Can not release object.");
		return false;
	}
}

