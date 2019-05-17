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

	//Returns the instance of the Actor
	virtual const AActor* GetChildActorReference() override { return this; };


public:	

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

	virtual const USkeletalMeshComponent* GetSkeletalMeshComponent() override { return WeaponSkeletalMesh; }

};
