// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerCar.generated.h"

UCLASS()
class TWOBETTERTHANONE_API ATriggerCar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerCar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement");
	FVector FinalLocation;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	bool IsGoingRight;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mechanics")
	AActor* Target;

private:
	FVector InitialLocation;
	FVector CurrentLocation;

};
