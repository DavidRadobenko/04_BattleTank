// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// +1 is max up movement, -1 is max down movement
	void Elevate(float relativeSpeed);

private:

	UPROPERTY(EditAnywhere, Category = Setup)
		float maxDegreesPerSecond = 20; // sensible default
	
	UPROPERTY(EditAnywhere, Category = Setup)
		float minElevationDegrees = 0;

	UPROPERTY(EditAnywhere, Category = Setup)
		float maxElevationDegrees = 30; //Maybe 40

};
