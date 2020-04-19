// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:


	
	/** This is Bound to the ScrollBox with the same name in the Blueprint */
	UPROPERTY(meta = (BindWidget))
		UScrollBox* ServerListScrollBox;

	/** This is Bound to the Button with the same name in the Blueprint */
	UPROPERTY(meta = (BindWidget))
		UButton* HostButton;

	/** This is Bound to the Button with the same name in the Blueprint */
	UPROPERTY(meta = (BindWidget))
		UButton* SearchButton;

	/** This is Bound to the Button with the same name in the Blueprint */
	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;


};
