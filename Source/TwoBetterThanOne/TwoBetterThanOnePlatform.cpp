// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoBetterThanOnePlatform.h"

// Sets default values
ATwoBetterThanOnePlatform::ATwoBetterThanOnePlatform()
	:IsRotating(false),
	IsGoingUp(false),
	RotationSpeed(20.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATwoBetterThanOnePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ATwoBetterThanOnePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRotating)
	{
		CurrentRotation = GetActorRotation();
		CurrentRotation.Pitch += RotationSpeed * DeltaTime;
		SetActorRotation(CurrentRotation);
		
		if ( (IsGoingUp && CurrentRotation.Pitch <= 0) || (!IsGoingUp && CurrentRotation.Pitch >= FinalDegrees) )
		{
			RotationSpeed *= -1;
			IsRotating = false;
			IsGoingUp = !IsGoingUp;
		}
	}
}

void ATwoBetterThanOnePlatform::ButtonPressed()
{
	if (!IsRotating)
		IsRotating = true;
}
