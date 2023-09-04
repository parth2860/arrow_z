// Copyright Epic Games, Inc. All Rights Reserved.

#include "op_worldGameMode.h"
#include "op_worldCharacter.h"
#include "UObject/ConstructorHelpers.h"

Aop_worldGameMode::Aop_worldGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
