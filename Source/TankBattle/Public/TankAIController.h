// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

private:

	ATank* MyTank = NULL;
	ATank* PlayerTank = NULL;

};
