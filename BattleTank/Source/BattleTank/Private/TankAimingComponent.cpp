// Copyright David Radobenko

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (ammo <= 0)
		firingState = EFiringState::NoAmmo;
	else if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds)
	{
		firingState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		firingState = EFiringState::Aiming;
	}
	else
		firingState = EFiringState::Locked;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// So first fire is after initial reload
	lastFireTime = FPlatformTime::Seconds();
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

void UTankAimingComponent::AimAt(FVector hitLocation)
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
		aimDirection = outLaunchVelocity.GetSafeNormal();
		
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (firingState == EFiringState::Aiming || firingState == EFiringState::Locked)
	{
		if (!barrel)
		{
			UE_LOG(LogTemp, Error, TEXT("UTankAimingComponent::Fire barrel is nullptr"));
			return;
		}

		if (!projectileBlueprint)
		{
			UE_LOG(LogTemp, Error, TEXT("UTankAimingComponent::Fire projectileBlueprint is nullptr, set it in the blueprint"));
			return;
		}

		// Spawns a projectile at the socket location of the barrel
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectlie"))
			);
		projectile->LaunchProjectile(launchSpeed);
		ammo--;
		lastFireTime = FPlatformTime::Seconds();
	}

	
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return firingState;
}

uint8 UTankAimingComponent::GetAmmoCount() const
{
	return ammo;
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

	//Always Yaw the shortest way
	barrel->Elevate(deltaRotator.Pitch);
	if(FMath::Abs(deltaRotator.Yaw) < 180)
		turret->Rotate(deltaRotator.Yaw);
	else
		turret->Rotate(-deltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!barrel) return false;
	
	return !barrel->GetForwardVector().Equals(aimDirection, 0.01);
}

