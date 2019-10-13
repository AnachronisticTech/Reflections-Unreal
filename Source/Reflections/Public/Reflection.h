// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Reflection.generated.h"

UCLASS()
class REFLECTIONS_API AReflection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReflection();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStaticMesh(UStaticMesh* StaticMeshToSet, UMaterialInterface* MaterialToSet);

	void SetLocationRotation(FVector Location, FRotator Rotation, FVector Scale);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UStaticMeshComponent* StaticMeshComponent  = nullptr;

};
