// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* MyTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerControlledTank();

	if (MyTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("The AI controlled tank is: %s"), *(MyTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No tank is possessed!"));
	}

	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("The AI thinks the player controlled tank is: %s"), *(PlayerTank->GetName()));
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

ATank* ATankAIController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}