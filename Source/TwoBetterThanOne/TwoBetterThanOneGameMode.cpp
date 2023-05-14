// Copyright Epic Games, Inc. All Rights Reserved.

#include "TwoBetterThanOneGameMode.h"
#include "TwoBetterThanOneCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

ATwoBetterThanOneGameMode::ATwoBetterThanOneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATwoBetterThanOneGameMode::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<APlayerStart> PlayerStartSubClass;
	PlayerStartSubClass = APlayerStart::StaticClass();
	TArray<AActor*> PlayersStart;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerStartSubClass, PlayersStart);
	

}
