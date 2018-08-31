// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "TankAimingComponent.h"
// Implicit dependancy on MovementComponent because of pathfinding logic

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Has No Aiming Component!"));

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && AimingComponent))
	{
		return;
	}

	if (MoveToActor(PlayerTank, AcceptanceRadius, true, true, false, 0, true) == EPathFollowingRequestResult::Failed)
	{
		UE_LOG(LogTemp, Error, TEXT("PathFollowing request failed!"))
	}

	FVector PlayerTankLocation = PlayerTank->GetActorLocation();
	AimingComponent->AimAt(PlayerTankLocation);
	AimingComponent->Fire();


}
