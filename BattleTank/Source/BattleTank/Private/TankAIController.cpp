// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	possessedTank = GetPossessedTank();
	if (possessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController player possessed Tank is: %s"), *possessedTank->GetName());
	} else
		UE_LOG(LogTemp, Warning, TEXT("AIController is not possessing a Tank"));
	
	playerTank = GetPlayerTank();
	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController player possessed Tank is: %s"), *playerTank->GetName());
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AIController is not finding the Player Tank"));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer();
}

ATank* ATankAIController::GetPossessedTank()
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::AimTowardsPlayer()
{
	if (!possessedTank) return;
	possessedTank->AimAt(playerTank->GetActorLocation());
}
