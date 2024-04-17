// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_PointScreenGameMode.h"
#include "TP_PointScreenCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATP_PointScreenGameMode::ATP_PointScreenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
