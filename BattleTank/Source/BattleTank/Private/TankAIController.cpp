// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	possessedTank = Cast<ATank>(GetPawn());	
	if (!possessedTank)
		UE_LOG(LogTemp, Error, TEXT("AIController could'nt find the Possessed Tank"));
	playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!playerTank)
		UE_LOG(LogTemp, Error, TEXT("AIController could'nt find the Player Tank"));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!playerTank) return;
	if (!possessedTank) return;

	possessedTank->AimAt(playerTank->GetActorLocation());
	possessedTank->Fire(); //TODO don't fire every frame
}
