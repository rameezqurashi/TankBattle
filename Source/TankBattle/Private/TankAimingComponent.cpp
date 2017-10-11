// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector & HitLocation, const float Launchspeed)
{
	TArray<AActor*> IgnoreList = { GetOwner() };
	FVector OutLaunchVelocity;
	ensure(Barrel);

	// Returns 0 if invalid path
	if (UGameplayStatics::SuggestProjectileVelocity(this, 
													OutLaunchVelocity, 
													Barrel->GetSocketLocation(FName("Projectile")), 
													HitLocation,
													Launchspeed, 
													false, 
													0.0, 
													0.0, 
													ESuggestProjVelocityTraceOption::TraceFullPath,
													FCollisionResponseParams::DefaultResponseParam, 
													IgnoreList, 
													false))
	{
		MoveBarrel(OutLaunchVelocity.GetSafeNormal());
		UE_LOG(LogTemp, Warning, TEXT("Tank %s should fire at: %s"), *(GetOwner()->GetName()), *OutLaunchVelocity.ToString());
	}
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	ensure(Barrel);
	FRotator BarrelRotation = Barrel->GetComponentRotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;
}
