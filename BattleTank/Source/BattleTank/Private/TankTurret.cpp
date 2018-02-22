// Copyright David Radobenko

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, +1);
	float rotationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rotation = RelativeRotation.Yaw + rotationChange;
	SetRelativeRotation(FRotator(0, rotation,0));
}


