// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"

#include "Grabber.generated.h"

class UInputComponent;
class UPhysicsHandleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REFLECTIONS_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere)
    float Reach = 100.0f;

    UPhysicsHandleComponent* PhysicsHandle = nullptr;

    UInputComponent* InputComponent = nullptr;

    bool bHasInputComponent = false;

    void FindPhysicsHandleComponent();
    void SetupInputComponent();
    void Grab();
    void Release();
    FHitResult GetFirstPhysicsBodyInReach() const;
    FVector GetReachLineStart() const;
    FVector GetReachLineEnd() const;

		
};
