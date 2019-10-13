// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectCube.h"
#include "Reflected_Cube.h"
#include "Mirror.h"

// Sets default values
AObjectCube::AObjectCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Mirror) return;

	// Determine reflection location
	FVector CubeLocation = GetActorLocation();
	FVector MirrorLocation = Mirror->GetActorLocation();
	FVector MirrorPlaneNormal = Mirror->GetActorForwardVector().GetSafeNormal();
	FVector ReflectionLocation = (2 * MirrorLocation) - CubeLocation + (2 * MirrorPlaneNormal * FVector::DotProduct((CubeLocation - MirrorLocation), MirrorPlaneNormal));
	ReflectionLocation.Z = CubeLocation.Z;

	// TODO: Get reflected rotation
	FRotator CubeRotation = GetActorRotation();
	FRotator ReflectionRotation = FRotator(
		CubeRotation.Pitch,
		-CubeRotation.Yaw,
		-CubeRotation.Roll
	);

	// Spawn reflection if it doesn't already exist
	if (!Reflection) {
		if (!ensure(ReflectionBlueprint)) return;
		Reflection = GetWorld()->SpawnActor<AReflected_Cube>(ReflectionBlueprint, ReflectionLocation, ReflectionRotation);
	}

	Reflection->SetActorLocation(ReflectionLocation);
	Reflection->SetActorRotation(ReflectionRotation);
	// UE_LOG(LogTemp, Warning, TEXT("Reflected location: %s"), *ReflectionLocation.ToString());

}

void AObjectCube::Initialise(AMirror* MirrorToSet) {
	Mirror = MirrorToSet;
}

