// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* MyTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerControlledTank();

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}