// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// +1 is max up movement, -1 is max down movement
	void Elevate(float relativeSpeed);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float maxDegreesPerSecond = 10; // sensible default
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float minElevationDegrees = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float maxElevationDegrees = 30; //Maybe 40

};
