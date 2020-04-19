// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ServerRowWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API UServerRowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//TextBlock that olds the name of the Server
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ServerNameTextBlock;

	//TextBlock that holds the number of players in the server
	UPROPERTY(meta = (BindWidget))
		UTextBlock* NumberOfPlayersText;

	/** The Buttton For Joining Session */
	UPROPERTY(meta = (BindWidget))
		UButton* JoinSessionButton;

	//Holds the index of the server
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int Index;
};
