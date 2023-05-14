// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TwoBetterThanOnePlatform.generated.h"

UCLASS()
class TWOBETTERTHANONE_API ATwoBetterThanOnePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATwoBetterThanOnePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	float FinalDegrees;

	UFUNCTION(BlueprintCallable)
	void ButtonPressed();

private:
	bool IsRotating;
	bool IsGoingUp;

	float RotationSpeed;

	FRotator CurrentRotation;
};
