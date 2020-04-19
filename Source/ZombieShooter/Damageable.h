// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * This Interface will be implemented by all actors that can be damaged.
 */
class ZOMBIESHOOTER_API IDamageable
{
	GENERATED_IINTERFACE_BODY()

	/**
	 * This Function is Called if a damageable object has been shot
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
		void TakeBulletDamage(float Damage);

	/**
	 * This function is called if a damageable object comes in contact with fire
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
		void TakeFireDamage();
	
	
};
