// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun_Interface.h"
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

	//Skeletal Mesh of the Gun
	UPROPERTY(EditAnywhere, Category="Components")
	USkeletalMesh* SkeletalMesh;

	//Skeletal Mesh Component Holding the Gun
	UPROPERTY(EditAnywhere, Category = "Components")
	USkeletalMeshComponent* WeaponSkeletalMesh;

	UPROPERTY()
	USoundBase* FireSound;

	UPROPERTY()
	UParticleSystem* FlashEmitter;

	UPROPERTY()
	UParticleSystemComponent* FlashEmitterComponent;



public:

	//Spawns the particle Effects like Flash or smoke at the muzzle of the Gun after it has been fired
	void SpawnParticleEffects();

	//Spawns a Gunshot sound and alerts AI Characters that a gun was just fired
	void SpawnGunShotSound(AActor* ShooterCharacter, UPawnNoiseEmitterComponent *PawnNoiseEmitter);




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
		float GetDamage() const { return Damage; }

	//-------------------------------END OF CALLABLE FUNCTIONS-----------------------//



	//--------------------------------INTERFACE IMOLEMENTATIONS-----------------------//

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actions")
		void FireGun(UCameraComponent* FollowCamera, AActor* NoiseMaker, UPawnNoiseEmitterComponent *PawnNoiseEmitter);
		virtual void FireGun_Implementation(UCameraComponent* FollowCamera, AActor* NoiseMaker, UPawnNoiseEmitterComponent *PawnNoiseEmitter) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actions")
		void ReloadGun();
		virtual void ReloadGun_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actions")
		int GetClipSizeOfGun();
		virtual int GetClipSizeOfGun_Implementation() override { return ClipSize; };

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Getters")
		int GetMaxAmmoOfGun();
		virtual int GetMaxAmmoOfGun_Implementation() override { return MaxAmmo; };

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Getters")
		int GetAmmoOfGun();
		virtual int GetAmmoOfGun_Implementation() override { return Ammo; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Getters")
		float GetFireRateOfGun();
		virtual float GetFireRateOfGun_Implementation() override { return FireRate; }

	//--------------------------------END OF INTERFACE IMOLEMENTATIONS-----------------------//

};
