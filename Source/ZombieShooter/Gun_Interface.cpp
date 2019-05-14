// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun_Interface.h"


// Add default functionality here for any IGun_Interface functions that are not pure virtual.

void IGun_Interface::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("A gun Has been fired Ammo: %d ClipSize: %d"), Ammo, ClipSize);
}
