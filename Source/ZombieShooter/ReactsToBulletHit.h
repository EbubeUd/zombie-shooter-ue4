// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ReactsToBulletHit.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UReactsToBulletHit : public UInterface
{
	GENERATED_BODY()
};

/**
 * This interface is going to be implemented by all actors that react to hit by a bullet
 */
class ZOMBIESHOOTER_API IReactsToBulletHit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	
};
