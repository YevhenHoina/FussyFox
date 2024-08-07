// Copyright Epic Games, Inc. All Rights Reserved.

#include "FussyFoxGameMode.h"
#include "FussyFoxPlayerController.h"
#include "FussyFoxCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFussyFoxGameMode::AFussyFoxGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFussyFoxPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}