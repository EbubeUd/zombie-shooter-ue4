// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "MainMenuWidget.h"
#include "Classes/Engine/GameInstance.h"
#include "ZombieShooterGameInstance.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API AMenuGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	AMenuGameMode();


	//Damage Effect Widgetj
	UPROPERTY()
		 UMainMenuWidget *MainMenu;

	UPROPERTY()
		TSubclassOf<UMainMenuWidget> MainMenuTemplate;


protected:
	void BeginPlay();


};
