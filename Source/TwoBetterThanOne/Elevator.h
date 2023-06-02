// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobilePlatform.h"
#include "Elevator.generated.h"

UCLASS()
class TWOBETTERTHANONE_API AElevator : public AMobilePlatform
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UFUNCTION(BlueprintCallable)
	void TriggerActivated();

private:
	void ChangeDirection();
};
