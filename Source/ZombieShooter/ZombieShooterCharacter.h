// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

 #pragma once
 
 #include "CoreMinimal.h"
#include "Engine/Engine.h"
 #include "GameFramework/Character.h"
 #include "Blueprint/UserWidget.h"
 #include "Runtime/Engine/Public/TimerManager.h"
 #include "AK47_Base.h"
 #include "EnemyKillFeedWidgetClass.h"
 #include "FPSHudWidgetClass.h"
 #include "CrossHairWidget.h"
 #include "Components/SceneCaptureComponent2D.h"
 #include "Enums/Enums.h"
 #include "M4A_Base.h"
 #include "Helpers/Mathematics.h"
 #include "Components/PawnNoiseEmitterComponent.h"
 #include "Components/AudioComponent.h"
 #include "Online.h"

 #include "ZombieShooterCharacter.generated.h"
 
 UCLASS(config=Game)
 class AZombieShooterCharacter : public ACharacter
{
	 GENERATED_BODY()

	


	//The Player's Id (Im My Case, the Steam Id)
//	 TSharedPtr<const FUniqueNetId> playerId;

	 //The PLayer's Nickname
	 FString PlayerNickName;


	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent *FollowCamera;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* ThirdPersonCamera;

	UPROPERTY()
		TSubclassOf<UFPSHudWidgetClass> FPSHudWidgetTemplate;

	//Damage Effect Widget
	UPROPERTY()
		UUserWidget *DamageEffectWidget;


	UPROPERTY()
		TSubclassOf<UUserWidget> DamageEffectWidgetTemplate;


	UPROPERTY()
		TSubclassOf<UCrossHairWidget> WBCrosshairWidgetTemplate;

	UPROPERTY()
		TSubclassOf<UEnemyKillFeedWidgetClass> EnemyKillfeedWidgetTemplate;


	//Weapon
	UPROPERTY()
		TSubclassOf<AAK47_Base> AK47WeaponClass;

	UPROPERTY()
		TSubclassOf<AM4A_Base> M4AWeaponClass;

	UPROPERTY()
		USoundBase* ReloadSound;

	UPROPERTY()
		UPawnNoiseEmitterComponent* PawnNoiseEmitter;

	UPROPERTY()
		USoundBase* InjuredSound;

	UPROPERTY()
		USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category="Camera")
		CameraPosition CameraPos;
public:
	AZombieShooterCharacter();

	UPROPERTY(VisibleAnywhere, Category = "Multiplayer")
		FString stringifiedPlayerId;


	//FPSHud Widget
	UPROPERTY()
		UFPSHudWidgetClass *FPSHudWidget;

	//WBCrosshair Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UCrossHairWidget* WBCrosshairWidget;

	//Enemy Kill feed Widget 
	UPROPERTY()
		UEnemyKillFeedWidgetClass* EnemyKillfeedWidget;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
		AWeapon_Base* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
		AWeapon_Base* PrimaryWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
		AWeapon_Base* SecondaryWeapon;

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		bool AddWeapon(AWeapon_Base* weapon);


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

	void CrouchPlayer();

	void Stand();

	void Sprint();

	/**Handler For Aiming Closely with the ADS Caera **/
	void AimDown();

	/**Handler For Cancelling aim and switching to the Follow Camera **/
	void StopAiming();

	/** Handler For Reducing the time left for the Characert to live **/
	void ReduceTimeLeftToLive();

	
	void SwitchWeapon();

	void SwitchWeapon(WeaponType weaponType, int index);


	UFUNCTION(BlueprintCallable, Category = "Weapons")
		void SwitchWeaponType();

	/** Defines Actions to occur when the character dies **/
	void Die();

	/**Toggles the Camera to be either Third Person Camera or First Person Character **/
	UFUNCTION(BlueprintCallable, Category="Camera")
	void SwitchCamera();
	
	/** Published whenever the Camera position has been switched **/
	UFUNCTION(BlueprintNativeEvent, Category = "Camera")
	void OnCameraPositionSwitched(CameraPosition cameraPosition);

	/**
	 * Switches the active camera to a specified one. Either First Person or third Person camera
	 */
	void SwitchCamera(CameraPosition cameraPosition);

	/** Tick Event. Calls on Every Frame **/
	void Tick(float DeltaTime);

	/** Called Once On the First Frame*/
	void BeginPlay();

	/**Called when the Player is Deactivated*/
	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UFUNCTION(BlueprintCallable, Category="Functions")
		void TriggerEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere, Category="Weapon Setup")
		TMap<WeaponAttachmentPosition, FName> WeaponSocketMap;


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

	UPROPERTY()
		bool bIsRecievingDamage;

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

	UPROPERTY()
		bool bIsDead;

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

	UPROPERTY(VisibleAnywhere, Category = "weapons")
		TArray<AWeapon_Base*> PrimaryWeapons;

	UPROPERTY(VisibleAnywhere, Category = "Weapons")
		TArray<AWeapon_Base*> SecondaryWeapons;

	UPROPERTY(VisibleAnywhere, Category="Weapons")
		int ActivePrimaryWeaponIndex;

	
	UPROPERTY(VisibleAnywhere, Category = "Weapons")
		int ActiveSecondaryWeaponIndex;

	UPROPERTY(VisibleAnywhere, Category = "Weapons")
		WeaponType ActiveWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AAK47_Base* AK47Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AM4A_Base *M4AWeapon;

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

