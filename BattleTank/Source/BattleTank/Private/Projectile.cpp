// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointer
	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	projectileMovementComponent->bAutoActivate = false;

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	launchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); 

	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	impactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	impactBlast->bAutoActivate = false;

	explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
	explosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::LaunchProjectile(float speed)
{
	projectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	launchBlast->Deactivate();
	impactBlast->Activate();
	explosionForce->FireImpulse();
	
	SetRootComponent(impactBlast);
	collisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		projectileDamage,
		GetActorLocation(),
		explosionForce->Radius, // for consistency
		UDamageType::StaticClass(),
		TArray<AActor*>() // damage all Actors
		);

	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AProjectile::OnTimerExpire, destroyDelay, false);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}
