// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ZombieShooterGameMode.h"
#include "ZombieShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZombieShooterGameMode::AZombieShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL) DefaultPawnClass = PlayerPawnBPClass.Class;
}

void AZombieShooterGameMode::BeginPlay() {
	Super::BeginPlay();
	MainCharacter = Cast<AZombieShooterCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

