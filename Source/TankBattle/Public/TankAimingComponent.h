// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	

	void AimAt(FVector & HitLocation, const float Launchspeed);

	void SetBarrelReference(UTankBarrel * BarrelToSet);

	void SetTurretReference(UTankTurret * TurretToSet);

private:
	UTankBarrel *Barrel = NULL;

	UTankTurret *Turret = NULL;

	void MoveBarrel(FVector AimDirection);
	
};
