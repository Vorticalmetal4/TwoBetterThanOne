// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  AElevator::TriggerActivated()
{
	if (HasMovement)
		ChangeDirection();
	else
		HasMovement = true;
}

void AElevator::ChangeDirection()
{
	IsGoingToFinal = !IsGoingToFinal;
	TargetLocation = (IsGoingToFinal) ? InitialLocation : FinalLocation;
}