// Fill out your copyright notice in the Description page of Project Settings.


#include "Reflectable.h"
#include "Reflection.h"
#include "Mirror.h"

// Sets default values
AReflectable::AReflectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReflectable::BeginPlay()
{
	Super::BeginPlay();
	Object = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(FName("StaticMesh")));
}

// Called every frame
void AReflectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Mirror) return;

	// Determine reflection location
	FVector CubeLocation = GetActorLocation();
	FVector MirrorLocation = Mirror->GetActorLocation();
	FVector MirrorPlaneNormal = Mirror->GetActorForwardVector().GetSafeNormal();
	FVector ReflectionLocation = (2 * MirrorLocation) - CubeLocation + (2 * MirrorPlaneNormal * FVector::DotProduct((CubeLocation - MirrorLocation), MirrorPlaneNormal));
	ReflectionLocation.Z = CubeLocation.Z;

	// Determine reflected rotation
	FRotator CubeRotation = GetActorRotation();
	FRotator ReflectionRotation = FRotator(
		CubeRotation.Pitch,
		-CubeRotation.Yaw,
		-CubeRotation.Roll
	);

	// Spawn reflection if it doesn't already exist
	if (!Reflection) {
		if (!ensure(ReflectionBlueprint)) return;
		Reflection = GetWorld()->SpawnActor<AReflection>(ReflectionBlueprint, ReflectionLocation, ReflectionRotation);

		if (!Object || !Reflection) return;
		Reflection->SetStaticMesh(Object->GetStaticMesh(), Object->GetMaterial(0));
	}

	Reflection->SetLocationRotation(ReflectionLocation, ReflectionRotation, GetActorScale3D());

}

void AReflectable::Initialise(AMirror* MirrorToSet) {
	Mirror = MirrorToSet;
}
