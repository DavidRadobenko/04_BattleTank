// Copyright David Radobenko

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	if (!leftTrackToSet || !rightTrackToSet) 
	{
		UE_LOG(LogTemp, Error, TEXT("UTankMovementComponent::Initialise one or both tracks are nullptr's"));
		return;
	}
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;

	//TODO prevent double speed due to dual control use
}

void UTankMovementComponent::IntendMoveForward(float yAxis)
{
	if (!leftTrack || !rightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("UTankMovementComponent::IntendMoveForward one or both tracks are nullptr's"));
		return;
	}
	leftTrack->SetThrottle(yAxis);
	rightTrack->SetThrottle(yAxis);
}

void UTankMovementComponent::IntendTurnRight(float xAxis)
{
	if (!leftTrack || !rightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("UTankMovementComponent::IntendMoveForward one or both tracks are nullptr's"));
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
