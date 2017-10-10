// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime);

private:
	ATank* GetControlledTank() const;
	
	void AimTowardsCrosshair() const;

	bool GetSightRayHitLocation(FVector &HitLocation) const;

	void GetCrossHairDirectionVector(FVector & CrossHairDirection) const;

	void AimAt(FVector &HitLocation) const;

	ATank* MyTank = NULL;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;

	// 10km reach of crosshair sight
	UPROPERTY(EditAnywhere)
	float Reach = 1000000.0;
};
