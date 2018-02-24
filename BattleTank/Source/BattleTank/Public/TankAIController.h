// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Forward decleration
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	APawn* playerTank;

	APawn* possessedTank;

	UTankAimingComponent* aimingComponent = nullptr;

	// How far can AI Tank can get
	float acceptanceRadius = 3000;
};
