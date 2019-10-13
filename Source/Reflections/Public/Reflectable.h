// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Reflectable.generated.h"

class AMirror;
class AReflection;

UCLASS()
class REFLECTIONS_API AReflectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReflectable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(AMirror* MirrorToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	AMirror* Mirror = nullptr;

	UStaticMeshComponent* Object = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AReflection> ReflectionBlueprint;

	// UPROPERTY()
	AReflection* Reflection;

};
