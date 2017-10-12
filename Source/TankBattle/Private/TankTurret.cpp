// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Make sure relativespeed does not exceed thresholds
	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);

	auto RotationChange = ClampedRelativeSpeed * MaxDegressPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}


