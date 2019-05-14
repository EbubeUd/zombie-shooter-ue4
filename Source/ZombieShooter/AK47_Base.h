// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Projectile_Base.h"
#include "ConstructorHelpers.h"
#include "AK47_Base.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AAK47_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAK47_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Skeletal Mesh of the Gun
	UPROPERTY()
		USkeletalMesh* SkeletalMesh;

	UPROPERTY()
		USkeletalMesh* M4ASkeletalMesh;

	//Skeletal Mesh Component Holding the Gun
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USkeletalMeshComponent* WeaponSkeletalMesh;


	//Skeletal Mesh Component Holding the Gun
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USkeletalMeshComponent* M4ASkeletalMeshComp;

	//Holds the Sound of the Weapon when fired
	UPROPERTY()
		USoundBase* FireSound;

	UPROPERTY()
		UParticleSystem* FlashEmitter;

	UPROPERTY()
		UParticleSystemComponent* FlashEmitterComponent;

	//This holds the Current Ammo in the Gun's Clip(Availabe number of bullets in the clip)
	UPROPERTY(visibleAnywhere, BlueprintReadOnly)
		int Ammo;

	//The Total Ammo Available in the Gun
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int MaxAmmo;

	//The Size of the Gun's Clip (Total bullets that can be fired before reloading)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int ClipSize;

	//The Delay between shots (in seconds) when the fire button is held down.
	UPROPERTY()
		float FireRate;

	//The Amount of Damage Each bullet of the Gun can cause on the Victim between 0 to 1. The Damage point will be subtracted from the victim's health otr Armor
	UPROPERTY()
		float Damage;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called When a Bullet is Fired
	void OnFire();

	//Called when the Gun is reloaded
	 void Reload();


	//Returns the Fire rate of The Gun( The Delay between two shots when the fire button is held down)
	float GetFireRate() const { return FireRate; }

	//Returns the Ammo Available in the Gun
	float GetAmmo() const { return Ammo; }

	//Increments the Ammo by the Number of clips
	void IncrementMaxAmmo() { MaxAmmo += ClipSize; }

	//Returns the Max Ammo
	float GetMaxAmmo() const { return MaxAmmo; }
	
	//Returns the Clip Size
	float GetClipSize() const { return ClipSize; }

	//Returns the Damage that the Gun Can inflict. (Ranges from 0 - 1)
	float GetDamage() const { return Damage; }

	void SwitchWeapon();


	USkeletalMeshComponent* GetSkeletalMeshComponent() const { return WeaponSkeletalMesh; }

};
