// Copyright David Radobenko
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	currentHealth = startingHealth;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = startingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Clamp<float>(damagePoints, 0, currentHealth);
	UE_LOG(LogTemp, Warning, TEXT("DamageAmount: %i Damage to Apply: %i"), damagePoints, damageToApply);
	currentHealth -= damageToApply;
	if (currentHealth <= 0)
		onDeath.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Health: %i"), currentHealth);
	return damageToApply;

}

float ATank::GetHealthPercent() const
{
	return (float)currentHealth / (float)startingHealth;
}
