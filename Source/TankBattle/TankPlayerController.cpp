// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	ATank* MyTank = GetControlledTank();

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

void ATankPlayerController::AimTowardsCrosshair()
{
	ATank* MyTank = GetControlledTank();

	if (!MyTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AimTowardsCrosshair cannot find player tank"));
		return;
	}
}


