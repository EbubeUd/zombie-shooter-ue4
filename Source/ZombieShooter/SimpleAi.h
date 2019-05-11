// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "ZombieShooterCharacter.h"
#include "Classes/Perception/PawnSensingComponent.h"
#include "Engine/GameEngine.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "SimpleAi.generated.h"

UCLASS()
class ZOMBIESHOOTER_API ASimpleAi : public ACharacter
{
	GENERATED_BODY()

		
public:
	// Sets default values for this character's properties
	ASimpleAi();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
		void OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume);

	UFUNCTION()
		void OnSeePawn(APawn *OtherPawn);
	

	//When set to false, the AI character can not take further damage till the impact process of the current Damage is done.
	bool bCanTakeDamage;	
	
	//Set to true if the AI Character Can see the Player
	bool bCanSeePlayer;	

	//The Handle that will be used to control the timer for moving the Character around at intervals
	FTimerHandle CharacterMovementTimerHandle;

	/** Called At intervals to move the Character from one place to thhe other **/
	void MoveCharacterAround();

	/**Called when the Player is Deactivated*/
	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY()
		AAIController* AICtrl;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Holds the Health of the Enemy
	UPROPERTY()
		float Health;

	//Holds the Radius in Float that the Character is allowed to Move to while roaming
	UPROPERTY()
		float MovementRadius;

	//Holds the name of the Enemy
	UPROPERTY(EditAnywhere, Category = "Biography")
		FString Name;
	
	UFUNCTION()
		void TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void TriggerHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
		AZombieShooterCharacter* MainCharacter;



	void Die();
	


};
