// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TwoBetterThanOneGameMode.generated.h"

UCLASS(minimalapi)
class ATwoBetterThanOneGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATwoBetterThanOneGameMode();

	virtual void BeginPlay();
};



