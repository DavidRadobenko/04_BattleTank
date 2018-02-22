// Copyright David Radobenko
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector hitLocation)
{
	if (!tankAimingComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ATank::AimAt tankAimingComponent is nullptr"));
		return;
	}
	tankAimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::Fire()
{
	if (!barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("ATank::Fire barrel is nullptr"));
		return;
	}
	if (!projectileBlueprint)
	{
		UE_LOG(LogTemp, Error, TEXT("ATank::Fire projectileBlueprint is nullptr, set it in the blueprint"));
		return;
	}

	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;

	if (isReloaded)
	{
		// Spawns a projectile at the socket location of the barrel
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectlie"))
			);
		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}
