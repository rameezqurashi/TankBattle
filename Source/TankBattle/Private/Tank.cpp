// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();

}

void ATank::AimAt(FVector & HitLocation) const
{
	if (ensure(TankAimingComponent))
	{
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
	else
	{
		return;
	}
}

void ATank::Fire()
{
	if (!ensure(Barrel))
		return;

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
	
	if (isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")),
			FActorSpawnParameters());

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}
