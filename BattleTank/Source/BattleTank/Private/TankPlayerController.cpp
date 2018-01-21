// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is not possesing a Tank"), *controlledTank->GetName());
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("PlayerController controlled Tank is: %s"), *controlledTank->GetName());
}
