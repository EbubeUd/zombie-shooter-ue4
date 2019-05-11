// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ZombieShooterCharacter.h"
#include "AmmoPickUp.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AAmmoPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* StaticMeshComp;


	UPROPERTY(EditAnywhere, Category = "Components")
		UBoxComponent* BoxCollisionComp;


	UPROPERTY()
		AZombieShooterCharacter* ShooterCharacter;

	UPROPERTY()
		USoundBase* PickupSound;



	/**
*	This is a signature function that  is called whenever the obstacle is hit by a bullet
*	The Parameters were gotten from PrimitiveComponent.h
*	FComponentHitSignature
*/
	UFUNCTION()
		void TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


	UPROPERTY()
		bool HasRecievedAmmo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
};
