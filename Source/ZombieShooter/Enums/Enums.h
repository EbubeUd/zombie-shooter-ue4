#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class Guns : uint8 
{
	AK47 UMETA(DisplayName="AK47"),
	M4A UMETA(DisplayName = "M4A")
};

UENUM(BlueprintType)
enum class CameraPosition : uint8
{
	FirstPersonCamera UMETA(DisplayName="FirstPersonCamera"),
	ThirdPersonCamera UMETA(DisplayName="ThirdPersonCamera")
};