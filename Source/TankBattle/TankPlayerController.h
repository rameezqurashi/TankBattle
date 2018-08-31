// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * Responsible for player aiming
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

private:
	void BeginPlay() override;

	void Tick(float DeltaTime);

	void AimTowardsCrosshair() const;

	bool GetSightRayHitLocation(FVector &HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;

	// 10km reach of crosshair sight
	UPROPERTY(EditDefaultsOnly)
	float Reach = 1000000.0;

	UTankAimingComponent* AimingComponent;
};
