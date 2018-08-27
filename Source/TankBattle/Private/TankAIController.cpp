// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* MyTank = Cast<ATank>(GetPawn());

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No player tank to aim at!"));
	}
	else
	{
		if (MoveToActor(PlayerTank, AcceptanceRadius, true, true, false, 0, true) == EPathFollowingRequestResult::Failed)
		{
			UE_LOG(LogTemp, Error, TEXT("PathFollowing request failed!"))
		}

		FVector PlayerTankLocation = PlayerTank->GetActorLocation();
		MyTank->AimAt(PlayerTankLocation);

		MyTank->Fire();
	}
}
