// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
private:
	ATank * controlledTank;

	UPROPERTY(EditAnywhere)
		float crossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float crossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
		float lineTraceRange = 1000000; //10km

	// Get the Controlled Tank
	ATank * GetControlledTank() const;

	// Moves the Tank barrel to the Aimed destination
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& outHitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;

};
