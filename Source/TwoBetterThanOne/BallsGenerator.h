// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.h"
#include "BallsGenerator.generated.h"

UCLASS()
class TWOBETTERTHANONE_API ABallsGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallsGenerator();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABall> BallClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UFUNCTION(BlueprintCallable)
	void SpawnBall();

private:
	float SpawnDistance;
};
