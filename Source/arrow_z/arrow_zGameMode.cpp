// Copyright Epic Games, Inc. All Rights Reserved.

#include "arrow_zGameMode.h"
#include "arrow_zCharacter.h"
#include "UObject/ConstructorHelpers.h"

Aarrow_zGameMode::Aarrow_zGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
