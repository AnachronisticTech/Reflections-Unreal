// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "ObjectCube.generated.h"

class AMirror;
class AReflected_Cube;

UCLASS()
class REFLECTIONS_API AObjectCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectCube();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(AMirror* MirrorToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	AMirror* Mirror = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AReflected_Cube> ReflectionBlueprint;

	// UPROPERTY()
	AReflected_Cube* Reflection;

};
