// Copyright David Radobenko

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	controlledTank = GetPawn();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("ATankPlayerController::BeginPlay controlledTank is nullptr"));
	}

	aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!aimingComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ATankPlayerController::BeginPlay aimingComponent is nullptr"));
		return;
	}

	FoundAimingComponent(aimingComponent);
		
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
	bool bGotHitLocation = GetSightRayHitLocation(hitLocation);
	if (bGotHitLocation)
	{
		if (!aimingComponent) return;
		aimingComponent->AimAt(hitLocation);
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
		return GetLookVectorHitLocation(lookDirection, outHitLocation);
	}
	return false;
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

void ATankPlayerController::SetPawn(APawn * inPawn)
{
	Super::SetPawn(inPawn);
	if (inPawn)
	{
		ATank* aControlledTank = Cast<ATank>(inPawn);
		if (aControlledTank) return;

		aControlledTank->onDeath.AddUniqueDynamic(this, &ATankPlayerController::OnControlledTankDeath);
	}
}

void ATankPlayerController::OnControlledTankDeath()
{
	StartSpectatingOnly();
}

