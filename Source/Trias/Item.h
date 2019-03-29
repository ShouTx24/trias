// Trias Development Team, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveObject.h"
#include "Item.generated.h"

UCLASS()
class TRIAS_API AItem : public AInteractiveObject
{
	GENERATED_BODY()
	
public:	
	
	AItem();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact() override;
	FString ItemName;

	UPROPERTY(EditAnywhere, Category = Item)
		UStaticMesh* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	UStaticMeshComponent* MeshComp;


	void PickedUp();

};
