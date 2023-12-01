// Copyright Epic Games, Inc. All Rights Reserved.

#include "SecretSantaGameMode.h"
#include "SecretSantaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASecretSantaGameMode::ASecretSantaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
