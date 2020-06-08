// Dactyl Games, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimeManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIAS_API UTimeManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimeManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	
	UPROPERTY(BlueprintReadWrite)
	float InGameTime = 180;
	
	UPROPERTY(BlueprintReadOnly)
	bool bInGameTimeRunning = true;

public:
	
	UFUNCTION(BlueprintCallable)
	float GetInGameTime();

	UFUNCTION(BlueprintCallable, Exec)
	void SetInGameTime(float NewTime);

	UFUNCTION(BlueprintCallable)
	void AddInGameTime(float AddedTime);
	
	UFUNCTION(BlueprintCallable)
	bool IsTimeRunning();

	UFUNCTION(BlueprintCallable, Exec)
	void SetTimeRunning(bool NewState);
	
	UFUNCTION(BlueprintCallable)
	float GetHour();
};
