// Copyright Epic Games, Inc. All Rights Reserved.

#include "MPFDevGameMode.h"
#include "MPFDevCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMPFDevGameMode::AMPFDevGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
