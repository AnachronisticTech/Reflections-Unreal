// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlockComponent.h"
#include "UnlockTrigger.h"
#include "ThirdPersonCharacter.h"

// Sets default values for this component's properties
UUnlockComponent::UUnlockComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUnlockComponent::BeginPlay()
{
	Super::BeginPlay();
    Owner = GetOwner();

	if (!PressurePlate) {
        UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *(GetOwner()->GetName()));
    }
	
}


// Called every frame
void UUnlockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalNumberOfPlayersOnPlate() >= NumberOfPlayersToUnlock) {
        OnUnlock.Broadcast();
    }
}

int32 UUnlockComponent::GetTotalNumberOfPlayersOnPlate() {
    int32 TotalPlayers = 0;
    TArray<AActor*> ActorsOnPlate;
    if (!PressurePlate) { return 0; }
    PressurePlate->GetOverlappingActors(ActorsOnPlate, AThirdPersonCharacter::StaticClass());

    for (const auto* Actor : ActorsOnPlate) {
		TotalPlayers += 1;
    }

    return TotalPlayers;
}

