// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!barrel) return;
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
		
		float time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), time);
	}
	else {
		float time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), time);
	}
		


	
	
}

void UTankAimingComponent::SetBarrel(UTankBarrel * barrelToSet)
{
	barrel = barrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - barrelRotator;

	barrel->Elevate(deltaRotator.Pitch); //TODO remove hard coded number
}

