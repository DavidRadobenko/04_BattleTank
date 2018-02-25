// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	possessedTank = GetPawn();	
	if (!possessedTank)
	{
		UE_LOG(LogTemp, Error, TEXT("ATankAIController::BeginPlay possessedTank is nullptr"));
	}

	playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("ATankAIController::BeginPlay playerTank is nullptr"));
	}

	aimingComponent = possessedTank->FindComponentByClass<UTankAimingComponent>();
	if (!aimingComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ATankAIController::BeginPlay aimingComponent is nullptr"));
	}
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

	aimingComponent->AimAt(playerTank->GetActorLocation());

	if(aimingComponent->GetFiringState() == EFiringState::Locked)
		aimingComponent->Fire();
}
