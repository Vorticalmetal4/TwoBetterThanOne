// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerCar.h"

// Sets default values
ATriggerCar::ATriggerCar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATriggerCar::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	TargetLocation = FinalLocation;
}

// Called every frame
void ATriggerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		CurrentLocation = GetActorLocation();
		Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
		CurrentLocation += Speed * DeltaTime * Direction;
		SetActorLocation(CurrentLocation);

		if ((CurrentLocation - TargetLocation).Size() <= 5)
		{
			IsGoingToFinal = !IsGoingToFinal;
			TargetLocation = (IsGoingToFinal) ? InitialLocation : FinalLocation;
		}
	}
}

