// Trias Development Team, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
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
	
	UFUNCTION(BlueprintCallable)
	virtual void Interact() override;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Item)
	FString ItemName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Item)
	FString ID;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Item)
	TArray<FString> Recipe;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Item)
	UStaticMesh* Model;

	UPROPERTY(VisibleDefaultsOnly, Category = Item)
	UStaticMeshComponent* MeshComp;

	UFUNCTION(BlueprintGetter)
	FString GetItemName();

	void PickedUp();

	virtual void Use();

};
