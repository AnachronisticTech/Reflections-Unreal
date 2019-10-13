// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    FindPhysicsHandleComponent();
    SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!PhysicsHandle) { return; }
    if (PhysicsHandle->GrabbedComponent) {
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }
}

void UGrabber::FindPhysicsHandleComponent() {
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
        UE_LOG(LogTemp, Error, TEXT("Physics Handle component missing for %s"), *(GetOwner()->GetName()));
    }
}

void UGrabber::SetupInputComponent() {

    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Input component missing for %s"), *(GetOwner()->GetName()));
    }
}

void UGrabber::Grab() {
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
    if (!PhysicsHandle) { return; }
    if (ActorHit) {
        PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
    }
}

void UGrabber::Release() {
    if (!PhysicsHandle) { return; }
    PhysicsHandle->ReleaseComponent();
}

FVector UGrabber::GetReachLineStart() const {
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
    
    return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd() const {
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
    
    FVector LineTraceDirection = PlayerViewPointRotation.Vector() * Reach;
    return PlayerViewPointLocation + LineTraceDirection;
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {

    FHitResult LineTraceHit;
    FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(LineTraceHit, GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), CollisionQueryParams);

    AActor* ActorHit = LineTraceHit.GetActor();

    return LineTraceHit;
}

