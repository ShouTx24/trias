// Trias Development Team, all rights reserved.

#include "Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	RootComponent = Root;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Mesh Component")));
	MeshComp->SetupAttachment(Root);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Interact()
{
	PickedUp();
}

void AItem::PickedUp()
{
	RootComponent->DestroyComponent();
	MeshComp->DestroyComponent();
}

void AItem::Use()
{
}

