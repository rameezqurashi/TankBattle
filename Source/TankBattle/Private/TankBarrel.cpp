// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Make sure relativespeed does not exceed thresholds
	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);

	auto ElevationChange = ClampedRelativeSpeed * MaxDegressPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	// Make sure elevation does not exceed thresholds
	auto ClampedNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(ClampedNewElevation, 0, 0));
}


