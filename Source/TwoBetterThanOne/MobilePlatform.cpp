// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePlatform.h"

// Sets default values
AMobilePlatform::AMobilePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMobilePlatform::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	FinalLocation = GetTransform().TransformPosition(FinalLocation);
	TargetLocation = FinalLocation;
	//GEngine->AddOnScreenDebugMessage(0 - 1, 5.f, FColor::Blue, FString::Printf(TEXT("Target location of %s: %s"), *GetName(), *TargetLocation.ToString()));
}

// Called every frame
void AMobilePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (HasMovement)
		{
			CurrentLocation = GetActorLocation();
			Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
			CurrentLocation += Speed * DeltaTime * Direction;
			SetActorLocation(CurrentLocation);

			if ((CurrentLocation - TargetLocation).Size() <= 5)
			{
				IsGoingToFinal = !IsGoingToFinal;
				TargetLocation = (IsGoingToFinal) ? InitialLocation : FinalLocation;
				if (!MovementInLoop)
					HasMovement = false;
			}
		}
	}
}

