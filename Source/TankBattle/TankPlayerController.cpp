// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	
	if (ensure(AimingComponent))
		FoundAimingComponent(AimingComponent);
	else 
		UE_LOG(LogTemp, Warning, TEXT("No Aiming Component!"));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() const
{
	if (!ensure(GetControlledTank()))
	{
		return;
	}

	FVector HitLocation;


	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	// Direction of crosshair and location of camera which crosshair is on
	FVector CrossHairDirection;
	FVector CameraWorldLocation;

	// Endpoint of crosshair ray cast
	FVector SightEndPoint;

	// Size of screen
	int32 XSize, YSize;
	GetViewportSize(XSize, YSize);

	// Convert crosshair position on screen to location and direction
	DeprojectScreenPositionToWorld
	(
		((float)XSize) * CrossHairXLocation,
		((float)YSize) * CrossHairYLocation,
		CameraWorldLocation,
		CrossHairDirection
	);
	SightEndPoint = CameraWorldLocation + CrossHairDirection*Reach;

	FHitResult HitResult;
	bool IsHitFound;

	IsHitFound = GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		CameraWorldLocation,
		SightEndPoint,
		ECollisionChannel::ECC_Visibility,
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	HitLocation = HitResult.Location;
	return IsHitFound;
}


