// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun_Interface.h"
#include "M4A_Base.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AM4A_Base : public AActor, public IGun_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AM4A_Base();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	

	virtual void OnFire() override;
	
};
