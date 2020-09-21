// Dactyl Games, all rights reserved.


#include "BuildingManager.h"

// Sets default values for this component's properties
UBuildingManager::UBuildingManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	if (!PhysicsHandleComponent) PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(FName("PhysicsHandleComponent"));
}


// Called when the game starts
void UBuildingManager::BeginPlay()
{
	Super::BeginPlay();
	TGI = Cast<UTriasGameInstance>(GetWorld()->GetGameInstance());
}


// Called every frame
void UBuildingManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandleComponent->GetGrabbedComponent())
	{
		FHitResult Hit;
		FVector Line;
		TGI->GetPlayerLookingAt(Hit, 450, Line);
		if (Hit.GetComponent() && Hit.GetComponent()->GetOwner()->GetClass()->IsChildOf<ABuildingElement>())
		{
			Line = Hit.GetComponent()->GetSocketLocation(FName(Hit.GetComponent()->GetName()));
			Line -= Cast<ABuildingElement>(PhysicsHandleComponent->GetGrabbedComponent()->GetOwner())->ReallocateElementToSocket(Hit);
		}
		PhysicsHandleComponent->GetGrabbedComponent()->SetWorldLocation(Line);
		
	}
}

ABuildingElement* UBuildingManager::SpawnElement(TSubclassOf<ABuildingElement> Element)
{
	UWorld* World = GetWorld();
	if (!World) return nullptr;
	ClassPointer = Element.Get();
	auto PE = World->SpawnActor(Element.Get());
	GrabElement(Cast<ABuildingElement>(PE));
	return Cast<ABuildingElement>(PE);
}

void UBuildingManager::GrabElement(ABuildingElement* PE)
{
	UPrimitiveComponent* PEP = Cast<UPrimitiveComponent>(PE->GetRootComponent());
	PhysicsHandleComponent->GrabComponentAtLocation(PEP, NAME_None, PE->GetTargetLocation());
}

bool UBuildingManager::PlaceElement()
{
	if (PhysicsHandleComponent->GetGrabbedComponent())
	{
		PhysicsHandleComponent->GetGrabbedComponent()->SetCollisionProfileName(FName("BlockAll"));
		TArray<USceneComponent*> Children = PhysicsHandleComponent->GetGrabbedComponent()->GetAttachChildren();
		for (USceneComponent* Child : Children)
		{
			Cast<USphereComponent>(Child)->SetCollisionProfileName(FName("IgnoreOnlyPawn"));
		}
		PhysicsHandleComponent->ReleaseComponent();
		SpawnElement(ClassPointer);
		return true;
	}
	else return false;
}

void UBuildingManager::CancelPlacement()
{
	auto GrabbedComponent = PhysicsHandleComponent->GetGrabbedComponent()->GetOwner();
	PhysicsHandleComponent->ReleaseComponent();
	GrabbedComponent->Destroy();
}

