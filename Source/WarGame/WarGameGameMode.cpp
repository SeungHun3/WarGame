// Copyright Epic Games, Inc. All Rights Reserved.

#include "WarGameGameMode.h"
#include "WarGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
AWarGameGameMode::AWarGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}
