// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyKillFeedWidgetClass.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API UEnemyKillFeedWidgetClass : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	//Holds the Name of the Enemy that was killed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface") 
		FString EnemyName;
	
	
	
};
