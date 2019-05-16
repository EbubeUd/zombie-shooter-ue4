// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ConstructorHelpers.h"
#include "Projectile_Base.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Gun_Interface.h"
#include "M4A_Base.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AM4A_Base : public AActor, public IGun_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AM4A_Base();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	USkeletalMeshComponent* RootComp;

	//Skeletal Mesh of the Gun
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USkeletalMesh* SkeletalMesh;

	//Skeletal Mesh Component Holding the Gun
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* WeaponSkeletalMesh;

	/** Override the base Function For Firing the Gun**/
	virtual void OnFire() override;

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
	
	USkeletalMeshComponent* GetSkeletalMeshComponent() const { return WeaponSkeletalMesh; }

};
