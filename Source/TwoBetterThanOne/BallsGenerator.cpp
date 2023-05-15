// Fill out your copyright notice in the Description page of Project Settings.


#include "BallsGenerator.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ABallsGenerator::ABallsGenerator()
	:SpawnDistance(-120.0f),
	IsMoving(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABallsGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallsGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsMoving)
	{
		CurrentLocation = FMath::VInterpTo(GetActorLocation(), DestinationLocation, DeltaTime, Speed);
		SetActorLocation(CurrentLocation);
	}
}


void ABallsGenerator::SpawnBall()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Z += SpawnDistance;

	GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocation, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
}

void ABallsGenerator::StartMovement()
{
	CurrentLocation = GetActorLocation();
	IsMoving = true;
}
