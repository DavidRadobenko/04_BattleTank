// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"

// Forwards declaration
class UTankBarrel; 
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* barrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* turretToSet);

	UFUNCTION(BlueprintCallable)
		void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* tankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Setup)
		UTankMovementComponent* movementComponent = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float launchSpeed = 4000; // TODO find sensible default
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float reloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> projectileBlueprint;

	

	// Local barrel reference for spawning projectile
	UTankBarrel* barrel = nullptr;

	double lastFireTime = 0;
};
