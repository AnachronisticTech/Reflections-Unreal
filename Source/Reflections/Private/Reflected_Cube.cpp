// Fill out your copyright notice in the Description page of Project Settings.


#include "Reflected_Cube.h"

// Sets default values
AReflected_Cube::AReflected_Cube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReflected_Cube::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("I'm reflected in the world"));
	
}

// Called every frame
void AReflected_Cube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
