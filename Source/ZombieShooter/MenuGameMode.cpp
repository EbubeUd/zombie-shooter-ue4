// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuGameMode.h"
#define SESSION_NAME  "My Session Game"

AMenuGameMode::AMenuGameMode() 
{
	MainMenuTemplate = LoadClass<UMainMenuWidget>(nullptr, TEXT("/Game/ThirdPersonCPP/Blueprints/Widgets/Menu.Menu_C"));
}


void AMenuGameMode::BeginPlay() {
	Super::BeginPlay();

	//Create the Main Menu widget and Add to viewpot
	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(this);
	MainMenu = CreateWidget<UMainMenuWidget>(gameInstance, MainMenuTemplate);
	MainMenu->AddToViewport();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	//Call the Init function in the Game Instance
	UZombieShooterGameInstance* ZombieGameInstance = Cast<UZombieShooterGameInstance>(UGameplayStatics::GetGameInstance(this));
	ZombieGameInstance->OnInit(MainMenu);


}
