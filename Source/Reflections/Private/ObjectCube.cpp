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

	FVector Location = FVector(0, 0, 0);

	if (!ensure(Mirror)) return;
	FVector MirrorDirection = Mirror->GetActorRightVector().GetSafeNormal();
	FVector CubeDirection = GetActorForwardVector().GetSafeNormal();
	FVector ReflectionVector = FVector(
		MirrorDirection.X * CubeDirection.X * -1,
		MirrorDirection.Y * CubeDirection.Y * -1,
		MirrorDirection.Z * CubeDirection.Z * -1
	);

	if (!ensure(ReflectionBlueprint)) return;
	Reflection = GetWorld()->SpawnActor<AReflected_Cube>(ReflectionBlueprint, Location, ReflectionVector.Rotation());
	
}

// Called every frame
void AObjectCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectCube::Initialise(AMirror* MirrorToSet) {}

