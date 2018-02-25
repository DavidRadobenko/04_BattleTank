// Copyright David Radobenko

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming State
UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading,
	NoAmmo
};

// Forwards Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

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

	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	uint8 GetAmmoCount() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState firingState = EFiringState::Reloading;

private:
	UTankBarrel * barrel = nullptr;

	UTankTurret* turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float reloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> projectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 4000; // TODO find sensible default

	double lastFireTime = 0;

	FVector aimDirection;

	uint8 ammo = 3;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(FVector aimDirection);
 
	bool IsBarrelMoving();
};
