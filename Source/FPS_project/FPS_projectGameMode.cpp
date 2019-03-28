// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FPS_projectGameMode.h"
#include "FPS_projectHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPS_projectGameMode::AFPS_projectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Player/Behaviour/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPS_projectHUD::StaticClass();
}
