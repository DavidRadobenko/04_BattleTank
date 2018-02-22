// Copyright David Radobenko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"

// Forwards declaration
class UTankBarrel; 
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable)
		void Fire();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		UTankAimingComponent* tankAimingComponent = nullptr;

public:	

private:

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 4000; // TODO find sensible default
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float reloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> projectileBlueprint;

	// Local barrel reference for spawning projectile
	UTankBarrel* barrel = nullptr; //TODO remove

	double lastFireTime = 0;
};
