// Copyright David Radobenko

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UTankAimingComponent::InitialiseAimingComponent(UTankBarrel * barrelToSet, UTankTurret * turretToSet)
{
	if (!(barrelToSet && turretToSet))
	{
		UE_LOG(LogTemp, Error, TEXT("UTankAimingComponent::InitialiseAimingComponent barrelToSet or turretToSet of %s is nullptr"), *GetOwner()->GetName());
		return;
	}
	barrel = barrelToSet;
	turret = turretToSet;
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("UTankAimingComponent::AimAt barrel of %s is nullptr"), *GetOwner()->GetName());
		return;
	}
	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
	// TODO bHaveAimingSolution will always return true, because in ATankPlayerController::GetLookVectorHitLocation we set the hitLocation to be 0,0,0 when hitting nothing in range.
	bool bHaveAimingSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	//Calculate the OutLaunchVelocity
	if (bHaveAimingSolution)
	{
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	if (!(barrel && turret))
	{
		UE_LOG(LogTemp, Error, TEXT("UTankAimingComponent::MoveBarrelTowards barrel or turret of %s is nullptr"), *GetOwner()->GetName());
		return;
	}

	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - barrelRotator;

	barrel->Elevate(deltaRotator.Pitch); //TODO remove hard coded number
	turret->Rotate(deltaRotator.Yaw);
}

