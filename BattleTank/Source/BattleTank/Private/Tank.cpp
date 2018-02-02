// Fill out your copyright notice in the Description page of Project Settings.
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

	// No need to protect pointer as added at construction
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATank::AimAt(FVector hitLocation)
{
	tankAimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel * barrelToSet)
{
	tankAimingComponent->SetBarrel(barrelToSet);
	barrel = barrelToSet;
}

void ATank::SetTurretReference(UTankTurret * turretToSet)
{
	tankAimingComponent->SetTurret(turretToSet);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
	if (!barrel) return;

	// Spawns a projectile at the socket location of the barrel
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
		projectileBlueprint,
		barrel->GetSocketLocation(FName("Projectile")),
		barrel->GetSocketRotation(FName("Projectlie"))
		);
	projectile->LaunchProjectile(launchSpeed);
}
