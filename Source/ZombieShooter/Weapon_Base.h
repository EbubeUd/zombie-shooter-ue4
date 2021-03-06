// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Enums/Enums.h"
#include "Weapon_Base.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AWeapon_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Base();

public:
	UPROPERTY()
		bool bHasBeenPicked;

	//The weapon type: It can be Primary or Secondary
	UPROPERTY(EditAnywhere, Category = "Weapon Components")
		WeaponType Type;


	//Root Component
	UPROPERTY(EditAnywhere, Category = "Components")
		USkeletalMeshComponent* RootComp;

	//Skeletal Mesh Component Holding the Gun
	UPROPERTY(EditAnywhere, Category = "Weapon Components")
		USkeletalMeshComponent* WeaponSkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon Components")
		USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = "Weapon Components")
		FString Name;

	//The Amount of Damage Each bullet of the Gun can cause on the Victim between 0 to 1. The Damage point will be subtracted from the victim's health otr Armor
	UPROPERTY(EditAnywhere, Category = "Weapon Components")
		float Damage;

	//The Volume of noise this weapon emits when fired
	UPROPERTY(EditAnywhere, Category = "Weapon Components")
		float NoiseVolume;

	UPROPERTY(EditAnywhere, Category = "Weapon Components")
		WeaponAttachmentPosition AttachmentPositionWhenActive;


	UPROPERTY(EditAnywhere, Category = "Weapon Components")
		WeaponAttachmentPosition AttachmentPositionWhenInactive;



	//This holds the Current Ammo in the Gun's Clip(Available number of bullets in the clip)		int Ammo;
	UPROPERTY(EditAnywhere, Category = "Gun Setup")
		int Ammo;

	//The Total Ammo Available in the Gun
	UPROPERTY(EditAnywhere, Category = "Gun Setup")
		int MaxAmmo;



	//The Size of the Gun's Clip (Total bullets that can be fired before reloading)
	UPROPERTY(EditAnywhere, Category = "Gun Setup")
		int ClipSize;

	//The Delay between shots (in seconds) when the fire button is held down.
	UPROPERTY(EditAnywhere, Category = "Gun Setup")
		float FireRate;

	//The Max Distance the Bullet Can Travel
	UPROPERTY(EditAnywhere, Category = "Gun Setup")
		float MaxDistanceBulletCanTravel;


	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	
	//-------------------------------CALLABLE FUNCTIONS-----------------------//

	//Returns the Fire rate of The Gun( The Delay between two shots when the fire button is held down)
	UFUNCTION(BlueprintCallable)
		float GetFireRate() const { return FireRate; }

	//Returns the Ammo Available in the Gun
	UFUNCTION(BlueprintCallable)
		int GetAmmo() const { return Ammo; }

	//Returns the Max Ammo
	UFUNCTION(BlueprintCallable)
		int GetMaxAmmo() const { return MaxAmmo; }

	//Returns the Clip Size
	UFUNCTION(BlueprintCallable)
		int GetClipSize() const { return ClipSize; }

	//Returns the Damage that the Gun Can inflict. (Ranges from 0 - 1)
	UFUNCTION(BlueprintCallable)
		virtual float GetDamage() const { return Damage; }

	UFUNCTION(BlueprintCallable, Category = "Actions")
		virtual void Reload();

	UFUNCTION(BlueprintCallable, Category = "Actions")
		virtual void Fire(UCameraComponent* FollowCamera, AActor* NoiseMaker, UPawnNoiseEmitterComponent *PawnNoiseEmitter);

	UFUNCTION(BlueprintCallable, Category = "Action")
		void IncrementMaxAmmo(int value);

	UFUNCTION(BlueprintNativeEvent, Category="Action Events")
		void OnFire(UCameraComponent* FollowCamera);

	UFUNCTION(BlueprintNativeEvent, Category = "Action Events")
		void OnEquip(AActor* Equipper);
	//-------------------------------END OF CALLABLE FUNCTIONS-----------------------//


};
