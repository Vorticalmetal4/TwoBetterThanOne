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
}

// Called every frame
void ATriggerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLocation = GetActorLocation();
	CurrentLocation.X += Speed * DeltaTime;
	SetActorLocation(CurrentLocation);

	if ((IsGoingRight && CurrentLocation.X >= FinalLocation.X) || (!IsGoingRight && CurrentLocation.X <= InitialLocation.X))
	{
		IsGoingRight = !IsGoingRight;
		Speed *= -1;
	}
}

