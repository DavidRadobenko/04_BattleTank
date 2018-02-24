// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	
}

void UTankTrack::ApplySidewaysForce()
{
	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//Work-out the required acceleration this frame to correct
	float deltaTime = GetWorld()->GetDeltaSeconds();
	FVector correctionAcceleration = -slippageSpeed / deltaTime * GetRightVector();
	//Calculate and apply sideways for (F = m a)
	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = tankRoot->GetMass() * correctionAcceleration / 2; // two tracks
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	currentThrottle = 0;
}

void UTankTrack::SetThrottle(float throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, +1);
}

void UTankTrack::DriveTrack() 
{
	//TODO Clamp actual throttle value
	FVector forceApplied = GetForwardVector() * currentThrottle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}


