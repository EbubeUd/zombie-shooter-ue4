// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/GameEngine.h"
#include "ZombieShooterCharacter.h"
#include "M4APickUp.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AM4APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AM4APickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	USkeletalMesh* SkeletalMesh;

	//SkeletalMesh Component of the Gun
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
		USkeletalMeshComponent* SkeletalMeshComp;


	//Collision Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* BoxCollisionComp;


	UFUNCTION()
		void TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//Prevents the collision event from happening more than once;
	bool bHasBeenPicked;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
