#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class Guns : uint8 
{
	AK47 UMETA(DisplayName="AK47"),
	M4A UMETA(DisplayName = "M4A")
};

UENUM(BlueprintType)
enum class WeaponType : uint8
{
	PrimaryWeapon UMETA(DisplayName = "Primary Weapon"),
	SecondaryWeapon UMETA(DisplayName = "Secondary Weapon")
};

UENUM(BlueprintType)
enum class CameraPosition : uint8
{
	FirstPersonCamera UMETA(DisplayName="FirstPersonCamera"),
	ThirdPersonCamera UMETA(DisplayName="ThirdPersonCamera")
};

UENUM(BlueprintType)
enum class WeaponAttachmentPosition : uint8
{
	Arm UMETA(DisplayName="Arm"),
	Wrist UMETA(DisplayName="Wrist"),
	LeftHolster UMETA(DisplayName="Left Pant Pocket"),
	RightHolster UMETA(DisplayName="Right Pant Pocket"),
	BackHolster UMETA (DisplayName="Back Holster")
};