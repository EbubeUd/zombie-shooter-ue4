// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.h"
#include "Particles/ParticleSystem.h"
#include "AK47_Base.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AAK47_Base : public AWeapon_Base
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAK47_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UParticleSystem* FlashEmitter;

	UPROPERTY()
	UParticleSystemComponent* FlashEmitterComponent;



public:

	//Spawns the particle Effects like Flash or smoke at the muzzle of the Gun after it has been fired
	void SpawnParticleEffects();

	//Spawns a Gunshot sound and alerts AI Characters that a gun was just fired
	void SpawnGunShotSound(AActor* ShooterCharacter, UPawnNoiseEmitterComponent *PawnNoiseEmitter);


protected:

	virtual void Fire(UCameraComponent* FollowCamera, AActor* NoiseMaker, UPawnNoiseEmitterComponent *PawnNoiseEmitter) override;

	virtual void Reload() override;


};
