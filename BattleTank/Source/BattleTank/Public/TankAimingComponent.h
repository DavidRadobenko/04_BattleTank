// Copyright David Radobenko

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming State
UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading
};

// Forwards Declaration
class UTankBarrel; 
class UTankTurret;

// Hold barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitialiseAimingComponent(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

	void AimAt(FVector hitLocation, float launchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus firingStatus = EFiringStatus::Aiming;

private:
	UTankBarrel * barrel = nullptr;

	UTankTurret* turret = nullptr;

	void MoveBarrelTowards(FVector aimDirection);
 
};
