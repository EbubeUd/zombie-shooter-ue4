// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ZombieShooterCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// AZombieShooterCharacter

AZombieShooterCharacter::AZombieShooterCharacter()
{


	////Get the player Id and assign it to the player Id Variable
	//playerId = onlineSubSystem->GetIdentityInterface()->GetUniquePlayerId(0);

	////Define the player's Nickname
	//PlayerNickName = onlineSubSystem->GetIdentityInterface()->GetPlayerNickname(0);

	//Define the PLayer Id String if the Id is not null
	//if (playerId->IsValid()) stringifiedPlayerId = playerId->ToString();
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	//Set The Initial Health and Armor
	Health = 1.f;
	Armor = .5f;
	TimeLeftToLive = 1800;

	//Set the Movement Speed
	MaxCrouchSpeed = 200.f;
	MaxWalkSpeed = 600.f;
	MaxSprintSpeed = 800.f;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(.0f, 540.f, 0.f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = .2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	PawnNoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>("PawnNoise");


	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm
	FName FollowCameraSocketName = TEXT("head"); //Get the name of the socket to attach the follow camera to
	FollowCamera->SetupAttachment(GetMesh(), FollowCameraSocketName);	//Attach the Camera the The Socket of the Mesh and Set the Mesh as its Parent
	

	//Create the ThirsPersonCamera
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
	ThirdPersonCamera->bUsePawnControlRotation = true;
	//ThirdPersonCamera->SetupAttachment(GetMesh());

	//Set Up The ADS Camera
	ADSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ADSCamera"));
	ADSCamera->SetupAttachment(GetMesh(), TEXT("Weapon_Attach"));

	//Set up the Mini Map Camera
	MinimapCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MiniMapCamera"));
	MinimapCamera->SetupAttachment(GetMesh());

	//Set up the Scene capture Component
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2d"));
	SceneCaptureComponent->SetupAttachment(MinimapCamera);

	//Set the Default Objective Text
	ObjectiveText = "Progress Through the Level";

	//Set the Selected Gun
	PrimaryWeapons.Init(nullptr, 5);
	SecondaryWeapons.Init(nullptr, 5);


	//Set up the Sounds
	InjuredSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/ThirdPersonCPP/Audio/No.No"));
	DeathSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/ThirdPersonCPP/Audio/Nooooo.Nooooo"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	WeaponSocketMap.Add(WeaponAttachmentPosition::Arm, TEXT("Arm"));
	WeaponSocketMap.Add(WeaponAttachmentPosition::Wrist, TEXT("Wrist"));
	WeaponSocketMap.Add(WeaponAttachmentPosition::LeftHolster, TEXT("LeftHolster"));
	WeaponSocketMap.Add(WeaponAttachmentPosition::RightHolster, TEXT("RightHolster"));
	WeaponSocketMap.Add(WeaponAttachmentPosition::BackHolster, TEXT("BackHolster"));
}


// Input

void AZombieShooterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AZombieShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AZombieShooterCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AZombieShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AZombieShooterCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AZombieShooterCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AZombieShooterCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AZombieShooterCharacter::OnResetVR);

	//Action 
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AZombieShooterCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AZombieShooterCharacter::StartAutomatedFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AZombieShooterCharacter::StopAutomatedFire);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AZombieShooterCharacter::CrouchPlayer);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AZombieShooterCharacter::Stand);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AZombieShooterCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AZombieShooterCharacter::Stand);

	PlayerInputComponent->BindAction("AimDown", IE_Pressed, this, &AZombieShooterCharacter::AimDown);
	PlayerInputComponent->BindAction("AimDown", IE_Released, this, &AZombieShooterCharacter::StopAiming);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AZombieShooterCharacter::Reload);

	PlayerInputComponent->BindAction("SwitchCamera", IE_Pressed, this, &AZombieShooterCharacter::SwitchCamera);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &AZombieShooterCharacter::SwitchWeapon);

}

void AZombieShooterCharacter::RegenerateArmor(float RateOfRegeneration) {

	//This function is Called at interval
	//If there is anything that can be done to stop the timer when the armor is full, please do.
	if (bIsRecievingDamage) return;	//Exit if the PLayer is currently receiving Damage or is in sight of an enemy
	if (Armor < 1.0f) {
		//Increase the Armor by the RateOfRegeneration
		Armor += RateOfRegeneration;
	}
	else {
		
		Armor = 1.0f;	//Set the Armor to 1.0f because it might have increased more than 1.0f 
	}
	
}

void AZombieShooterCharacter::Fire()
{
	if (bIsReloading || bIsSprinting) return;	//Exit if the Player is Reloading or sprinting
	if (!PawnNoiseEmitter) return;
	UCameraComponent* CameraInUse = (bIsAiming) ? ADSCamera : FollowCamera;
	if (!CameraInUse) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Camera is null"));
		return;
	}
	if (EquippedWeapon == nullptr)
	{
		//Perform the combat action

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Equipped Gun U Object is null"));
		return;
	}

	if(!PawnNoiseEmitter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Pawn Noise Emitter is null"));
		return;
	}

	if (EquippedWeapon) EquippedWeapon->Fire(CameraInUse, this, PawnNoiseEmitter);
}

void AZombieShooterCharacter::Reload()
{
	StopAiming();	//Stop the Character From Aiming when About to reload
	if (!EquippedWeapon) return;	//Exit if the Equipped weapon is null
	if (bIsReloading) return;	//Exit if the player is already reloading
	if (EquippedWeapon->GetClipSize() == EquippedWeapon->GetMaxAmmo()) return;	//Exit if the Player Has full Ammo
	bIsReloading = true;
	UGameplayStatics::PlaySound2D(this, ReloadSound);	//Play the reload sound
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AZombieShooterCharacter::StopReload, 2.5f, true, 2.5f);	//Set IsReloading to false when the animation is done playing. the Animation length was checked and found to be 3.3 secs, but it can be set to a desired time
}

void AZombieShooterCharacter::StopReload()
{
	bIsReloading = false;
	if (EquippedWeapon) EquippedWeapon->Reload();
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);	//Clear the Timer After Stopping the reload Animation;
}

void AZombieShooterCharacter::StartAutomatedFire()
{
	//AutomatedFireTimerDelegate.BindUFunction(this, FName("Fire"));
	bIsFiring = true;
	if (!EquippedWeapon) return;
	float FireRate = EquippedWeapon->GetFireRate();
	GetWorldTimerManager().SetTimer(AutomatedFireTimerHandle, this, &AZombieShooterCharacter::Fire, FireRate, true, 0.f);
}

void AZombieShooterCharacter::StopAutomatedFire()
{
	GetWorld()->GetTimerManager().ClearTimer(AutomatedFireTimerHandle);
	bIsFiring = false;
}

void AZombieShooterCharacter::CrouchPlayer()
{
	if (bIsSprinting) return;	//Prevents the Character from crouching if he is sprinting
	bIsCrouching = true;	//Enables the Crouch animation
	Crouch();	//Call the In Built Crouch Function;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeed = MaxCrouchSpeed;	//Reduces the speed of the player 
	
}

void AZombieShooterCharacter::Stand()
{
	bIsSprinting = false;	//Disables the sprint animation
	bIsCrouching = false;	//Disables the Crouch animation
	UnCrouch();		//Call the In Built function to disable the Crouch
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;	//Set the 
}

void AZombieShooterCharacter::Sprint() 
{
	
	if (bIsCrouching || bIsAiming) return;	//Don't sprint if the Character is crouching or aiming
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
}

void AZombieShooterCharacter::AimDown()
{
	if (bIsReloading || bIsSprinting) return;	//Stop the Character from Aiming when he is reloading or sprinting
	FollowCamera->Deactivate();
	ADSCamera->Activate();
	if (bIsAiming && bIsAiming)
	{
		//reduce the Walk Speed to half of the crouch speed if the character is also aiming down
		GetCharacterMovement()->MaxWalkSpeed = MaxCrouchSpeed / 2;
	}
	else 
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxCrouchSpeed;
	}
	
	bIsAiming = true;
}

void AZombieShooterCharacter::StopAiming()
{
	ADSCamera->Deactivate();
	SwitchCamera(CameraPos);
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	bIsAiming = false;
}

void AZombieShooterCharacter::ReduceTimeLeftToLive()
{
	if (bHasLifeTimeExpired) return;	//Exit if the Life Time is Expired

	if (TimeLeftToLive < 1) {
		//Expire the Lifetime if the countdown is done. And Stop the Timer
		GetWorld()->GetTimerManager().ClearTimer(LifeTimerHandle);
		bHasLifeTimeExpired = true;
		return;
	}
	TimeLeftToLive--;
}

void AZombieShooterCharacter::SwitchWeapon()
{
	int index = 0;
	switch(ActiveWeaponType)
	{
		case WeaponType::PrimaryWeapon:
			index = ActivePrimaryWeaponIndex == (PrimaryWeapons.Num() - 1) ? 0 : ActivePrimaryWeaponIndex + 1;
			SwitchWeapon(ActiveWeaponType, index);
			break;
		case WeaponType::SecondaryWeapon:
			index = ActiveSecondaryWeaponIndex == (SecondaryWeapons.Num() - 1) ? 0 : ActiveSecondaryWeaponIndex + 1;
			SwitchWeapon(ActiveWeaponType, index);
			break;
	}
}

void AZombieShooterCharacter::SwitchWeapon(WeaponType weaponType, int index)
{
	switch (weaponType)
	{
		case WeaponType::PrimaryWeapon:
			if(PrimaryWeapons.Num() > index)
			{
				PrimaryWeapon = PrimaryWeapons[index];
				ActivePrimaryWeaponIndex = index;
				ActiveWeaponType = WeaponType::PrimaryWeapon;
				EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocketMap[EquippedWeapon->AttachmentPositionWhenInactive]);
				EquippedWeapon = PrimaryWeapon;
				EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocketMap[EquippedWeapon->AttachmentPositionWhenActive]);
				EquippedWeapon->OnEquip(this);
			}

			break;
		case WeaponType::SecondaryWeapon:
			if (SecondaryWeapons.Num() > index)
			{
				SecondaryWeapon = SecondaryWeapons[index];
				ActiveSecondaryWeaponIndex = index;
				EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocketMap[EquippedWeapon->AttachmentPositionWhenInactive]);
				EquippedWeapon = SecondaryWeapon;
				EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocketMap[EquippedWeapon->AttachmentPositionWhenActive]);
				ActiveWeaponType = WeaponType::SecondaryWeapon;
				EquippedWeapon->OnEquip(this);

			}
	
			break;
	}
}

bool AZombieShooterCharacter::AddWeapon(AWeapon_Base* weapon)
{
	switch (weapon->Type)
	{
		case WeaponType::PrimaryWeapon:
			for (int i = 0; i < PrimaryWeapons.Num(); i++)
			{
				if (PrimaryWeapons[i] != nullptr && weapon != nullptr)
				{
					if (PrimaryWeapons[i]->Name == weapon->Name)
					{
						return false;
					}
				}
			
			}
			if (ActiveWeaponType == weapon->Type) EquippedWeapon = weapon;
			PrimaryWeapons.Add(weapon);
			SwitchWeapon(weapon->Type, PrimaryWeapons.Find(weapon));
		return true;
		case WeaponType::SecondaryWeapon:
			for (int i = 0; i < SecondaryWeapons.Num(); i++)
			{
				if (SecondaryWeapons[i] != nullptr && weapon != nullptr)
				{
					if (SecondaryWeapons[i]->Name == weapon->Name)
					{
						return false;
					}
				}
			}
			if (ActiveWeaponType == weapon->Type) EquippedWeapon = weapon;
			SecondaryWeapons.Add(weapon);
			SwitchWeapon(weapon->Type, SecondaryWeapons.Find(weapon));
		return true;
	}
	return false;
}


void AZombieShooterCharacter::SwitchWeaponType()
{
	switch (ActiveWeaponType)
	{
	case WeaponType::PrimaryWeapon:
		SwitchWeapon(WeaponType::SecondaryWeapon, ActiveSecondaryWeaponIndex);
		break;
	case WeaponType::SecondaryWeapon:
		SwitchWeapon(WeaponType::PrimaryWeapon, ActivePrimaryWeaponIndex);
		break;
	}
}



void AZombieShooterCharacter::Die()
{
	bIsDead = true;
	UGameplayStatics::SpawnSound2D(this, DeathSound, 1.f);

}

void AZombieShooterCharacter::SwitchCamera()
{
	switch (CameraPos)
	{
	case CameraPosition::FirstPersonCamera:
		SwitchCamera(CameraPosition::ThirdPersonCamera);
		break;
	case CameraPosition::ThirdPersonCamera:
		SwitchCamera(CameraPosition::FirstPersonCamera);
		break;
	}
}

void AZombieShooterCharacter::SwitchCamera(CameraPosition cameraPosition)
{
	switch (cameraPosition)
	{
	case CameraPosition::FirstPersonCamera:
		FollowCamera->Activate();
		ThirdPersonCamera->Deactivate();
		break;
	case CameraPosition::ThirdPersonCamera:
		ThirdPersonCamera->Activate();
		FollowCamera->Deactivate();
		break;
	}
	CameraPos = cameraPosition;
	OnCameraPositionSwitched(CameraPos);
}

void AZombieShooterCharacter::TakeDamage(float RateOfDamage)
{
	//Deduct the Rate of Damage From the Armor
	if (bIsDead) return;
	Armor -= RateOfDamage;
	//Check if the Armor has gone below 0, then deduct from the health
	if (Armor < 0.f)
	{
		Health += Armor;
		Armor = 0;
	}
	if (Health < 0.f) {
		Die();
	}
	else {
		UGameplayStatics::SpawnSound2D(this, InjuredSound, 1.f);
	}

	//Display the Damage Effect Widget (Red Vignette)
	DamageEffectWidget = CreateWidget<UUserWidget>(GetGameInstance(), DamageEffectWidgetTemplate);
	DamageEffectWidget->AddToViewport();
}

void AZombieShooterCharacter::ShowKillFeed(FString EnemyName)
{
	UGameInstance* gameInstance = GetGameInstance();
	EnemyKillfeedWidget = CreateWidget<UEnemyKillFeedWidgetClass>(gameInstance, EnemyKillfeedWidgetTemplate);
	EnemyKillfeedWidget->EnemyName = EnemyName;
	EnemyKillfeedWidget->AddToViewport();
}

void AZombieShooterCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AZombieShooterCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AZombieShooterCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AZombieShooterCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AZombieShooterCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AZombieShooterCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AZombieShooterCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AZombieShooterCharacter::Tick(float DeltaTime) {
	
	Super::Tick(DeltaTime);
	
	//Spread the CrossHair based on the Character's speed
	if ((!bIsAiming) && (WBCrosshairWidget)) {
		float VelocityLength = GetVelocity().Size();
		WBCrosshairWidget->PlayerVelocity = MapRangeClamped(VelocityLength, 0.f, 450.f, 5.f, 80.f);
		WBCrosshairWidget->SetCrossHairSpread();
	}
}

void AZombieShooterCharacter::BeginPlay() {
	//Call BeginPlay() in the Parent Class. Essential for code below this line to work efficiently
	Super::BeginPlay();

	//Get An Instance of the World
	UWorld* const World = GetWorld();

	//Fetch the Widget Templates 
	FPSHudWidgetTemplate = LoadClass<UFPSHudWidgetClass>(nullptr, TEXT("/Game/ThirdPersonCpp/Blueprints/Widgets/FPSHud.FPSHud_C"));
	EnemyKillfeedWidgetTemplate = LoadClass<UEnemyKillFeedWidgetClass>(nullptr, TEXT("/Game/ThirdPersonCPP/Blueprints/Widgets/KillFeed.KillFeed_C"));
	DamageEffectWidgetTemplate = LoadClass<UUserWidget>(nullptr, TEXT("/Game/ThirdPersonCpp/Blueprints/Widgets/DamageEffect.DamageEffect_C"));
	WBCrosshairWidgetTemplate = LoadClass<UCrossHairWidget>(nullptr, TEXT("/Game/ThirdPersonCPP/Blueprints/Widgets/DynamicCrossHair.WBCrosshair_C"));
	HitMarkerWidgetTemplate = LoadClass<UUserWidget>(nullptr, TEXT("/Game/ThirdPersonCPP/Blueprints/Widgets/HitMarker.HitMarker_C"));

	//Fetch the Sounds
	ReloadSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/ThirdPersonCPP/Audio/reload.reload"));

	//Spawn the weapons
	AK47Weapon = World->SpawnActor<AAK47_Base>(AAK47_Base::StaticClass(), GetActorLocation(), GetActorRotation()); 
	M4AWeapon = World->SpawnActor<AM4A_Base>(AM4A_Base::StaticClass(), GetActorLocation(), GetActorRotation());

	//Get the name of the character's socket to attach the Spawned Weapons to and Attach the weapons
	FName WeaponSocketName = TEXT("Weapon_Attach"); 
	AK47Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocketName);
	M4AWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocketName);


	//Display the FPSHud widget on the viewport
	FPSHudWidget = CreateWidget<UFPSHudWidgetClass>(GetGameInstance(), FPSHudWidgetTemplate);
	//FPSHudWidget->PlayerId = stringifiedPlayerId;
	//FPSHudWidget->PlayerNickname = PlayerNickName;
	FPSHudWidget->AddToViewport();

	//Create the  WBCrosshair widget and add to the View Port
	/*WBCrosshairWidget = CreateWidget<UCrossHairWidget>(GetGameInstance(), WBCrosshairWidgetTemplate);
	WBCrosshairWidget->AddToViewport();*/


	//Start the Timer for Regenerating the Armor
	ArmorRegenerationTimerDelegate.BindUFunction(this, FName("RegenerateArmor"), 0.05f);
	GetWorldTimerManager().SetTimer(ArmorRegenerationTimerHandle, ArmorRegenerationTimerDelegate, 1.0f,true);


	//Start the Timer for reducing the time left to live
	GetWorldTimerManager().SetTimer(LifeTimerHandle, this, &AZombieShooterCharacter::ReduceTimeLeftToLive, 1.f, true, 1.f);

	StopAiming();	//Sets the Follow Camera as the default Camera and disables the ADS Aim Camera till its needed.


	FollowCamera->Deactivate();
	ThirdPersonCamera->Activate();

}

void AZombieShooterCharacter::OnCameraPositionSwitched_Implementation(CameraPosition cameraPosition)
{

}

 void AZombieShooterCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	 Super::EndPlay(EndPlayReason);
	//clear ALL timers that belong to this (Actor) instance.
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}


 void AZombieShooterCharacter::TriggerEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
 {
	 AWeapon_Base* weapon = Cast<AWeapon_Base>(OtherActor);

	 if (weapon != nullptr)
	 {
		 if (weapon->bHasBeenPicked) return;	
		 weapon->bHasBeenPicked = true;
		 FPSHudWidget->PlayAnimation(FPSHudWidget->M4APickUpAnimation);
		 USoundBase* PickupSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/ThirdPersonCPP/Audio/reload.reload"));
		 UGameplayStatics::PlaySound2D(this, PickupSound);
		 AddWeapon(weapon);
	 }
 }

