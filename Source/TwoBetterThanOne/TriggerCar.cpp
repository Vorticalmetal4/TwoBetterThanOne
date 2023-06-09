// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerCar.h"

// Sets default values
ATriggerCar::ATriggerCar():
	ActorsInsideTrigger(0)
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

}

