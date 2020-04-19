// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Engine/GameEngine.h"
#include "ConstructorHelpers.h"
#include "Damageable.h"
#include "Components/PrimitiveComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "DrawDebugHelpers.h"

#include "Gun_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGun_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZOMBIESHOOTER_API IGun_Interface
{
	GENERATED_IINTERFACE_BODY()

protected:

	//This holds the Current Ammo in the Gun's Clip(Available number of bullets in the clip)		int Ammo;
		int Ammo;
	//The Total Ammo Available in the Gun
		int MaxAmmo;

	//The Size of the Gun's Clip (Total bullets that can be fired before reloading)
		int ClipSize;

	//The Delay between shots (in seconds) when the fire button is held down.
		float FireRate;

	//The Amount of Damage Each bullet of the Gun can cause on the Victim between 0 to 1. The Damage point will be subtracted from the victim's health otr Armor
		float Damage;

	//The Max Distance the Bullet Can Travel
		float MaxDistanceBulletCanTravel;

	//The Volume of noise the gun emits
		float NoiseVolume;
		
public:

	
	virtual void OnFire(UCameraComponent* FollowCamera);


	//-----------------------------BASE FUNCTIONS------------------------------------//

	/**There is a default function for reload which all guns have but they Can Uveride it if they wish**/
	void Reload();

	//Increments the Ammo by the Number of clips when the owner Of the Gun Picks Up an Ammo
	void IncrementMaxAmmo();

	//------------------------------END OF BASE FUNCTIONS-----------------------------//




	//-----------INTERFACE FUNCTIONS START--------------//

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actions")
		void FireGun(UCameraComponent* FollowCamera, AActor* NoiseMaker, UPawnNoiseEmitterComponent *PawnNoiseEmitter);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actions")
		void ReloadGun();

	//------------End Of Interface Functions --------------//






	//--------------- HELPER FUNCTIONS START -------------------//
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Getters")
		int GetClipSizeOfGun();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Getters")
		int GetMaxAmmoOfGun();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Getters")
		int GetAmmoOfGun();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Getters")
		float GetFireRateOfGun();

	//--------------- HELPER FUNCTIONS END -------------------//



};
