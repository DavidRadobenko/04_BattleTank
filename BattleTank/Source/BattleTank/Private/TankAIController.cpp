// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	possessedTank = Cast<ATank>(GetPawn());	
	playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!(playerTank && possessedTank))
	{
		UE_LOG(LogTemp, Error, TEXT("ATankAIController::Tick playerTank or possessedTank of %s is nullptr"), *GetOwner()->GetName());
		return;
	}

	// Move towards the Player
	MoveToActor(playerTank, acceptanceRadius); 

	possessedTank->AimAt(playerTank->GetActorLocation());
	possessedTank->Fire();
}
