// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	MyTank = GetControlledTank();
	PlayerTank = GetPlayerControlledTank();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No player tank to aim at!"));
	}
	else
	{
		FVector PlayerTankLocation = PlayerTank->GetActorLocation();
		MyTank->AimAt(PlayerTankLocation);
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