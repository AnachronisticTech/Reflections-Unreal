// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectableMobile.h"
#include "Reflection.h"
#include "Mirror.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AReflectableMobile::AReflectableMobile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Object = Cast<UStaticMeshComponent>(GetRootComponent());
    SetMobility(EComponentMobility::Movable);
}

void AReflectableMobile::BeginPlay() {
    Super::BeginPlay();
    if (HasAuthority()) {
        SetReplicates(true);
        SetReplicateMovement(true);
        GlobalStartLocation = GetActorLocation();
        GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
    }
}

void AReflectableMobile::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);

	// Move the platform
    if (HasAuthority() && ActiveTriggers > 0) {
        FVector Location = GetActorLocation();
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += Speed * DeltaSeconds * Direction;
        SetActorLocation(Location);

        if (FVector::Dist(Location, GlobalStartLocation) >= FVector::Dist(GlobalStartLocation, GlobalTargetLocation)) {
            FVector SwapedLocation = GlobalStartLocation;
            GlobalStartLocation = GlobalTargetLocation;
            GlobalTargetLocation = SwapedLocation;
        }

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
}

void AReflectableMobile::Initialise(AMirror* MirrorToSet) {
	Mirror = MirrorToSet;
}

void AReflectableMobile::AddActiveTrigger() {
    ActiveTriggers += 1;
}

void AReflectableMobile::RemoveActiveTrigger() {
    if (ActiveTriggers > 0) {
        ActiveTriggers -= 1;
    }
}

