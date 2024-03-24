// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_AuroraGameMode.h"
#include "Project_AuroraPlayerController.h"
#include "Project_AuroraCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_AuroraGameMode::AProject_AuroraGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProject_AuroraPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}