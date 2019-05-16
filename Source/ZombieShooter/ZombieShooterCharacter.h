// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "AK47_Base.h"
#include "EnemyKillFeedWidgetClass.h"
#include "FPSHudWidgetClass.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Enums/Enums.h"
#include "M4A_Base.h"
#include "ZombieShooterCharacter.generated.h"

UCLASS(config=Game)
class AZombieShooterCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent *FollowCamera;

	

	UPROPERTY()
		TSubclassOf<UFPSHudWidgetClass> FPSHudWidgetTemplate;

	//Damage Effect Widget
	UPROPERTY()
		UUserWidget *DamageEffectWidget;


	UPROPERTY()
		TSubclassOf<UUserWidget> DamageEffectWidgetTemplate;


	UPROPERTY()
		TSubclassOf<UUserWidget> WBCrosshairWidgetTemplate;

	UPROPERTY()
		TSubclassOf<UEnemyKillFeedWidgetClass> EnemyKillfeedWidgetTemplate;


	//Weapon
	UPROPERTY()
		TSubclassOf<AAK47_Base> AK47WeaponClass;

	UPROPERTY()
		TSubclassOf<AM4A_Base> M4AWeaponClass;

	UPROPERTY()
		USoundBase* ReloadSound;

public:
	AZombieShooterCharacter();

	//WBCrosshair Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UUserWidget* WBCrosshairWidget;

	//Enemy Kill feed Widget 
	UPROPERTY()
		UEnemyKillFeedWidgetClass* EnemyKillfeedWidget;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;




protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/**Handler for firing a bulletrom the weapon**/
	void Fire();

	/**Handler for reloading the weapon*/
	void Reload();

	/**Handler for stopping the reload animation*/
	void StopReload();

	/** Handler for Automated Fire When The Shoot button is held down **/
	void StartAutomatedFire();

	/** Handler for Stopping Automated Fire When the Shoot Button is released **/
	void StopAutomatedFire();

	void Crouch();

	void Stand();

	void Sprint();

	/**Handler For Aiming Closely with the ADS Caera **/
	void AimDown();

	/**Handler For Cancelling aim and switching to the Follow Camera **/
	void StopAiming();

	/** Handler For Reducing the time left for the Characert to live **/
	void ReduceTimeLeftToLive();

	/** Handler For Switching the Gun that the Character is currently using among the available Guns He has **/
	void SwitchGun();

	/** Tick Event. Calls on Every Frame **/
	void Tick(float DeltaTime);

	/** Called Once On the First Frame*/
	void BeginPlay();

	/**Called when the Player is Deactivated*/
	void EndPlay(const EEndPlayReason::Type EndPlayReason);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	//FPSHud Widget
	UPROPERTY()
		UFPSHudWidgetClass *FPSHudWidget;

	//Holds the Health Of the Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Health;

	//Holds the Armor of the Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Armor;

	//Is true when the life Count down Timer is done Counting
	bool bHasLifeTimeExpired;

	//Determines if the Character is Crouching
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsCrouching;	

	//Determines if the Character is Sprinting
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsSprinting;

	//Determines if the Character is Reloading
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsReloading;

	UPROPERTY()
		bool bIsFiring;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString ObjectiveText;

	//Determines if the Character is Aiming
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsAiming;

	//Holds the time left for the Character to live in seconds.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int TimeLeftToLive;

	UPROPERTY()
		float MaxWalkSpeed;

	UPROPERTY()
		float MaxCrouchSpeed;

	UPROPERTY()
		float MaxSprintSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bHasPickedM4A;

	/**Regenerates the plaer's  Armor After Damage
	*@Param fRate - Holds the Rate in float to add to the user's Armor
	*/
	UFUNCTION()
	void RegenerateArmor(float RateOfRegeneration = 0.01f);

	/**Reduces the player's  Armor or health After Damage
	*@Param fRate - Holds the Rate in float to add to the user's Armor
	*/
	UFUNCTION()
	void TakeDamage(float RateOfDamage = 0.05f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AAK47_Base* AK47Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AM4A_Base* M4AWeapon;

	/**ADS Camera for Aiming */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		 UCameraComponent* ADSCamera;

	/**Mini Map Camera * */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		 UCameraComponent* MinimapCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USceneCaptureComponent2D* SceneCaptureComponent;

	UPROPERTY()
		UUserWidget *HitMarkerWidget;


	UPROPERTY()
		TSubclassOf<UUserWidget> HitMarkerWidgetTemplate;


	/** Displays the Kill feed when an enemy has been killed. It is set as public because it will be called by the enemy that was killed before he dies **/
	void ShowKillFeed(FString EnemyName);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
		Guns SelectedGun;

protected:
	FTimerDelegate ArmorRegenerationTimerDelegate;
	FTimerHandle ArmorRegenerationTimerHandle;

	FTimerDelegate AutomatedFireTimerDelegate;
	FTimerHandle AutomatedFireTimerHandle;

	FTimerHandle ReloadTimerHandle;

	FTimerHandle LifeTimerHandle;
};

