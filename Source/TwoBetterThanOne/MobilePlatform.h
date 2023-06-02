// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MobilePlatform.generated.h"

UCLASS()
class TWOBETTERTHANONE_API AMobilePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMobilePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	FVector InitialLocation;
	FVector Direction;
	FVector CurrentLocation;
	FVector TargetLocation;

	bool IsGoingToFinal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (MakeEditWidget = true));
	FVector FinalLocation;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	bool HasMovement;
	UPROPERTY(EditAnywhere, Category = "Movement")
	bool MovementInLoop;
};
