// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlockTrigger.h"
#include "Components/BoxComponent.h"

// Sets default values
AUnlockTrigger::AUnlockTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!TriggerVolume) { return; }
	SetRootComponent(TriggerVolume);

}

// Called when the game starts or when spawned
void AUnlockTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnlockTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

