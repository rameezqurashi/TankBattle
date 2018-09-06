// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::AimAt(FVector & HitLocation)
{
	TArray<AActor*> IgnoreList = { GetOwner() };
	FVector OutLaunchVelocity;
	if (!ensure(Barrel))
		return;

	// Returns 0 if invalid path
	if (UGameplayStatics::SuggestProjectileVelocity(this, 
													OutLaunchVelocity, 
													Barrel->GetSocketLocation(FName("Projectile")), 
													HitLocation,
													LaunchSpeed, 
													false, 
													0.0, 
													0.0, 
													ESuggestProjVelocityTraceOption::DoNotTrace,
													FCollisionResponseParams::DefaultResponseParam, 
													IgnoreList, 
													false))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(Barrel))
		return;
	if (!ensure(Turret))
		return;
	FRotator BarrelRotation = Barrel->GetComponentRotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Rotate(DeltaRotation.Yaw);
}

void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet))
	{
		return;
	}

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint))
		return;

	if (FiringStatus != EFiringStatus::Reloading)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")),
			FActorSpawnParameters());

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (ensure(Barrel))
		return !(Barrel->GetForwardVector().Equals(AimDirection, .01));
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO BARREL IN IS BARREL MOVING METHOD"));
		return false;
	}

}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}
