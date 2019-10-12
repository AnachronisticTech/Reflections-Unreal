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
	UE_LOG(LogTemp, Warning, TEXT("I'm in the world"));
	
}

// Called every frame
void AObjectCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Mirror) return;

	FVector CubeLocation = GetActorLocation();
	FVector MirrorLocation = Mirror->GetActorLocation();
	FVector MirrorPlaneNormal = Mirror->GetActorForwardVector().GetSafeNormal();
	FVector ReflectionLocation = (2 * MirrorLocation) - CubeLocation + (2 * MirrorPlaneNormal * FVector::DotProduct((CubeLocation - MirrorLocation), MirrorPlaneNormal));

	// TODO: Get reflected rotation

	// Spawn reflection if it doesn't already exist
	if (!Reflection) {
		if (!ensure(ReflectionBlueprint)) return;
		Reflection = GetWorld()->SpawnActor<AReflected_Cube>(ReflectionBlueprint, ReflectionLocation, FRotator(0,0,0));
	}

}

void AObjectCube::Initialise(AMirror* MirrorToSet) {
	Mirror = MirrorToSet;
}

