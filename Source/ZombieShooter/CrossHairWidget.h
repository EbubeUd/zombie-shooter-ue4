// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrossHairWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API UCrossHairWidget : public UUserWidget
{
	GENERATED_BODY()
public:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "User Interface")
			float PlayerVelocity;
	
		UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
			void SetCrossHairSpread();
};
