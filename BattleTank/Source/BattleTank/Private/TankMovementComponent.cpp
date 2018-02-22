// Copyright David Radobenko

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::InitialiseMovementComponent(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	if (!(leftTrackToSet && rightTrackToSet))
	{
		UE_LOG(LogTemp, Error, TEXT("UTankMovementComponent::InitialiseMovementComponent leftTrackToSet or rightTrackToSet of %s is nullptr"), *GetOwner()->GetName());
		return;
	}
			
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;

	
}

void UTankMovementComponent::IntendMoveForward(float yAxis)
{
	if (!(leftTrack && rightTrack))
	{
		UE_LOG(LogTemp, Error, TEXT("UTankMovementComponent::IntendMoveForward leftTrack or rightTrack of %s is nullptr"), *GetOwner()->GetName());
		return;
	}
	leftTrack->SetThrottle(yAxis);
	rightTrack->SetThrottle(yAxis);
}

void UTankMovementComponent::IntendTurnRight(float xAxis)
{
	if (!(leftTrack && rightTrack))
	{
		UE_LOG(LogTemp, Error, TEXT("UTankMovementComponent::IntendMoveForward leftTrack or rightTrack of %s is nullptr"), *GetOwner()->GetName());
		return;
	}
	leftTrack->SetThrottle(xAxis);
	rightTrack->SetThrottle(-xAxis);
	
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super as we're replacing the functionality
	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float forwardThrow = FVector::DotProduct(tankForward, AIForwardIntention);
	IntendMoveForward(forwardThrow);

	float rightThrow = FVector::CrossProduct(tankForward, AIForwardIntention).Z;
	IntendTurnRight(rightThrow);
}
