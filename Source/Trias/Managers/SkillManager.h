// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIAS_API USkillManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY()
	int Condition = 1;
	
	UPROPERTY()
	int Strength = 1;
	
	UPROPERTY()
	int Crafting = 1;
	
	UPROPERTY()
	int Archery = 1;
	
	UPROPERTY()
	int Shooting = 1;
	
	UPROPERTY()
	int Sneak = 1;
	
	UPROPERTY()
	int Cooking = 1;

public:		
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCondition();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetStrength();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetArchery();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetShooting();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetSneak();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCooking();

	UFUNCTION(BlueprintCallable)
	void ProgressCondition(int Progress);

	UFUNCTION(BlueprintCallable)
	void ProgressStrength(int Progress);

	UFUNCTION(BlueprintCallable)
	void ProgressArchery(int Progress);

	UFUNCTION(BlueprintCallable)
	void ProgressShooting(int Progress);

	UFUNCTION(BlueprintCallable)
	void ProgressSneak(int Progress);

	UFUNCTION(BlueprintCallable)
	void ProgressCooking(int Progress);


};
