// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* MyTank = GetControlledTank();

	if (MyTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("The AI controlled tank is: %s"), *(MyTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No tank is possessed!"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
