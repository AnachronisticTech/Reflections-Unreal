// Fill out your copyright notice in the Description page of Project Settings.


#include "Reflection.h"
#include "Engine/StaticMesh.h"

// Sets default values
AReflection::AReflection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AReflection::BeginPlay()
{
	Super::BeginPlay();
    if (HasAuthority()) {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}

// Called every frame
void AReflection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReflection::SetStaticMesh(UStaticMesh* StaticMeshToSet, UMaterialInterface* MaterialToSet) {
	auto StaticMeshComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(FName("StaticMesh")));
	if (!StaticMeshComponent) return;
	StaticMeshComponent->SetStaticMesh(StaticMeshToSet);
	StaticMeshComponent->SetMaterial(0, MaterialToSet);
}

void AReflection::SetLocationRotation(FVector Location, FRotator Rotation, FVector Scale) {
	if (HasAuthority()) {
		SetActorLocation(Location);
		SetActorRotation(Rotation);
		SetActorScale3D(Scale);
	}
}

