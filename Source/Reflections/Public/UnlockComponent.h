// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnlockComponent.generated.h"

class AUnlockTrigger;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnlockEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REFLECTIONS_API UUnlockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnlockComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(BlueprintAssignable)
    FUnlockEvent OnUnlock;

    // UPROPERTY(BlueprintAssignable)
    // FDoorEvent OnClose;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    int32 GetTotalNumberOfPlayersOnPlate();
    
    UPROPERTY(EditAnywhere)
	AUnlockTrigger* PressurePlate = nullptr;

    UPROPERTY(EditAnywhere)
    int32 NumberOfPlayersToUnlock = 1;

    AActor* Owner = nullptr;

};
