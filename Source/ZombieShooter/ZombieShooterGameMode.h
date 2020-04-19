// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ZombieShooterCharacter.h"

#include "ZombieShooterGameMode.generated.h"

UCLASS(minimalapi)
class AZombieShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AZombieShooterGameMode();
	//AZombieShooterCharacter* MainCharacter;	

protected:
	void BeginPlay();
	

};



