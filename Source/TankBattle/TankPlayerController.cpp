// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	ATank* MyTank = GetControlledTank();

	if (MyTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("The player controlled tank is: %s"), *(MyTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No tank is possessed!"));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


