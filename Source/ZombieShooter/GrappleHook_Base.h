// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Weapon_Base.h"
#include "GrappleHook_Base.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AGrappleHook_Base : public AWeapon_Base
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrappleHook_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	



	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
		virtual void Fire(UCameraComponent* FollowCamera, AActor* NoiseMaker, UPawnNoiseEmitterComponent *PawnNoiseEmitter) override;

		virtual void Reload() override;


};
