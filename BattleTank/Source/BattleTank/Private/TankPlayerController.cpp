// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is not possesing a Tank"), *controlledTank->GetName());
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("PlayerController controlled Tank is: %s"), *controlledTank->GetName());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!controlledTank) return;

	FVector hitLocation; //Out parameter
	if (GetSightRayHitLocation(hitLocation))
	{
		if (!controlledTank)
		{
			UE_LOG(LogTemp, Error, TEXT("Player Controller is missing the controlled Tank"));
			return;
		}
		controlledTank->AimAt(hitLocation);
	}


}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	int32 viewPortSizeX, viewPortSizeY;

	GetViewportSize(viewPortSizeX, viewPortSizeY);

	FVector2D screenLocation = FVector2D(viewPortSizeX * crossHairXLocation, viewPortSizeY * crossHairYLocation);

	FVector lookDirection;

	if (GetLookDirection(screenLocation, lookDirection))
	{
		GetLookVectorHitLocation(lookDirection, outHitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation; // To be discarded

	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const
{
	FHitResult hitResult;
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + lookDirection * lineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility))
	{
		hitLocation = hitResult.Location;
		return true;
	}
	hitLocation = FVector(0);
	return false;
}

