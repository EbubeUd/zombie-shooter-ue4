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
#include "Gun_Interface.h"
#include "ConstructorHelpers.h"
#include "AK47_Base.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AAK47_Base : public AActor, public IGun_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAK47_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/** Override the base Function For Firing the Gun**/
	virtual void OnFire() override;

	//Returns the Fire rate of The Gun( The Delay between two shots when the fire button is held down)
	UFUNCTION(BlueprintCallable)
	float GetFireRate() const { return FireRate; }

	//Returns the Ammo Available in the Gun
	UFUNCTION(BlueprintCallable)
	float GetAmmo() const { return Ammo; }


	//Returns the Max Ammo
	UFUNCTION(BlueprintCallable)
	float GetMaxAmmo() const { return MaxAmmo; }

	//Returns the Clip Size
	UFUNCTION(BlueprintCallable)
	float GetClipSize() const { return ClipSize; }

	//Returns the Damage that the Gun Can inflict. (Ranges from 0 - 1)
	UFUNCTION(BlueprintCallable)
	float GetDamage() const { return Damage; }


};
