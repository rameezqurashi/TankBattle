// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
}

void UTankAimingComponent::AimAt(FVector & HitLocation, const float Launchspeed)
{
	TArray<AActor*> IgnoreList = { GetOwner() };
	FVector OutLaunchVelocity;
	ensure(Barrel);

	// Returns 0 if invalid path
	if (UGameplayStatics::SuggestProjectileVelocity(this, 
													OutLaunchVelocity, 
													Barrel->GetSocketLocation(FName("Projectile")), 
													HitLocation,
													Launchspeed, 
													false, 
													0.0, 
													0.0, 
													ESuggestProjVelocityTraceOption::DoNotTrace,
													FCollisionResponseParams::DefaultResponseParam, 
													IgnoreList, 
													false))
	{
		MoveBarrel(OutLaunchVelocity.GetSafeNormal());
		UE_LOG(LogTemp, Warning, TEXT("Tank %s should fire at: %s"), *(GetOwner()->GetName()), *OutLaunchVelocity.ToString());
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	ensure(Barrel);
	FRotator BarrelRotation = Barrel->GetComponentRotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;
}
