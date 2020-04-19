// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Damageable.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/GameEngine.h"
#include "Fire.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UParticleSystemComponent* ParticleSysytemComp;

	UPROPERTY()
	UParticleSystem* ParticleSystem;

	UPROPERTY()
	USoundBase* FireSound;

	UPROPERTY(VisibleAnywhere, Category="Audio")
	UAudioComponent* AudioComp;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		UCapsuleComponent* CapsuleComp;

	UPROPERTY()
		UStaticMeshComponent* StaticMeshRootComp;

	UFUNCTION()
		void InflictDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//Will be used to reset the value of bCanInflictDamage to true;
	UPROPERTY()
	FTimerHandle BurnTimer;

	//Will be used to delay the damage effect the fire has on the damageable object at intervals.
	UPROPERTY()
	bool bCanInflictDamage;

	UFUNCTION()
	void ResetCanInflictDamage();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
