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
	GENERATED_BODY()

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
public:

	
	virtual void OnFire(UCameraComponent* FollowCamera);

	/**There is a default function for reload which all guns have but they Can Uveride it if they wish**/
	void Reload();

	//Increments the Ammo by the Number of clips
	void IncrementMaxAmmo() { MaxAmmo += ClipSize; }

	virtual const USkeletalMeshComponent* GetSkeletalMeshComponent() { return nullptr; };

	virtual const AActor* GetChildActorReference() { return nullptr; };

	virtual void CustomFireEventForWeapon(FHitResult& OutHit) {};
protected: 


	//Holds the Sound of the Weapon when fired
		USoundBase* FireSound;

		UParticleSystem* FlashEmitter;

		UParticleSystemComponent* FlashEmitterComponent;



};
