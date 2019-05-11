// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSHudWidgetClass.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API UFPSHudWidgetClass : public UUserWidget
{
	GENERATED_BODY()
public:

	//Holds the health of the Main Character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
		float MainCharacterHealth;

	//Holds the Body Armor of the main Character 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
		float MainCharacterBodyArmor;
	
	//Holds the Weapon Armor of the main Character 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
		int MainCharacterWeaponAmmo;
};
