// Copyright Epic Games, Inc. All Rights Reserved.

#include "Puzzle3DGameMode.h"
#include "Puzzle3DCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzle3DGameMode::APuzzle3DGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
