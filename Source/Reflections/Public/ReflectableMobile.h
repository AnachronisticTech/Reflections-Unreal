// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "ReflectableMobile.generated.h"

class AMirror;
class AReflection;

UCLASS()
class REFLECTIONS_API AReflectableMobile : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReflectableMobile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(AMirror* MirrorToSet);

    void AddActiveTrigger();
    
    void RemoveActiveTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	AMirror* Mirror = nullptr;

	UStaticMeshComponent* Object = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AReflection> ReflectionBlueprint;

	AReflection* Reflection;

    UPROPERTY(EditAnywhere, Category = "Setup")
    float Speed = 5; // cm/s

    FVector GlobalStartLocation;
    FVector GlobalTargetLocation;

    UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
    FVector TargetLocation;

    UPROPERTY(EditAnywhere)
    int32 ActiveTriggers = 1;

};
