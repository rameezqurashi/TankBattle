// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	if (!(GetPawn())) { return; }
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (ensure(AimingComponent))
		FoundAimingComponent(AimingComponent);
	else 
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Has No Aiming Component!"));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() const
{
	if (!ensure(AimingComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player has no aiming component!"));
		return;
	}

	FVector HitLocation;
	bool bHaveHitLocation = GetSightRayHitLocation(HitLocation);

	if (bHaveHitLocation)
	{
		AimingComponent->AimAt(HitLocation);
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


