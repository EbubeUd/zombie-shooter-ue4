// Fill out your copyright notice in the Description page of Project Settings.

#include "M4A_Base.h"


// Sets default values
AM4A_Base::AM4A_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Ammo = 50;
	MaxAmmo = 450;
	ClipSize = 50;
}

// Called when the game starts or when spawned
void AM4A_Base::BeginPlay()
{
	Super::BeginPlay();
	Fire();
}



// Called every frame
void AM4A_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

