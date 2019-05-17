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

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
			 void TakeBulletDamage(float Damage);
public:
	
	
};
