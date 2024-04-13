// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleShooterGameMode.h"
#include "SimpleShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASimpleShooterGameMode::ASimpleShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

