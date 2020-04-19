// Fill out your copyright notice in the Description page of Project Settings.

#include "M4A_Base.h"


// Sets default values
AM4A_Base::AM4A_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set the Properties of the weapon
	FireRate = .5f;
	MaxAmmo = 750;
	ClipSize = 50;
	Ammo = ClipSize;
	Damage = .1f;
	MaxDistanceBulletCanTravel = 2000.f;
	NoiseVolume = 100.f;
	
	RootComp = CreateDefaultSubobject<USkeletalMeshComponent>("RootComponent");
	SetRootComponent(RootComp);

	//Set the Skeletal Mesh of the Weapon
	SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/ThirdPersonCPP/Blueprints/Weapons/M4A/M4A1.M4A1_weapon002'"));
	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponSkeletalMesh");
	if (SkeletalMesh) WeaponSkeletalMesh->SetSkeletalMesh(SkeletalMesh);
	WeaponSkeletalMesh->SetupAttachment(RootComp);

	//Set up the Location and rotation of the Gun
	WeaponSkeletalMesh->SetRelativeLocation(FVector(31.3f, -25.2f, -117.f));	//Set the location of the Skeletal mesh To fit the Pivot of the Root Component
	WeaponSkeletalMesh->SetRelativeScale3D(FVector(3.f));	//Set the Scale of the Weapon to match The scale of other Actors in the game.
	WeaponSkeletalMesh->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));	//Rotate the Skeletal Mesh to fit into the Weapon_Attach socket of the Character Holding the Gun.

	//Emitter
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	FlashEmitter = PS.Object;
}

// Called when the game starts or when spawned
void AM4A_Base::BeginPlay()
{
	Super::BeginPlay();
	FireSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/ThirdPersonCPP/Audio/Ak.Ak"));
}

void AM4A_Base::SpawnParticleEffects()
{
	//Spawn Emitter
	FlashEmitterComponent = UGameplayStatics::SpawnEmitterAtLocation(this, FlashEmitter, WeaponSkeletalMesh->GetSocketLocation("Muzzle"));
	FlashEmitterComponent->SetWorldScale3D(FVector(.05f, .05f, .05f));
}

void AM4A_Base::SpawnGunShotSound(AActor * ShooterCharacter, UPawnNoiseEmitterComponent * PawnNoiseEmitter)
{
	//Spawn a GunShot 
	UGameplayStatics::PlaySound2D(this, FireSound, .5f);

	//Make A Noise So the AI Characters Can be alerted
	PawnNoiseEmitter->MakeNoise(ShooterCharacter, NoiseVolume, ShooterCharacter->GetActorLocation());
}

void AM4A_Base::FireGun_Implementation(UCameraComponent* FollowCamera, AActor* ShooterCharacter, UPawnNoiseEmitterComponent *PawnNoiseEmitter)
{
	//Exit if the Character does not have Enough Ammo 
	if (Ammo < 1) return;

	//Exit if the Follow Camera, Shooter or PawnNoise Emitter is Null
	if (!FollowCamera || !ShooterCharacter || !PawnNoiseEmitter) return;

	//Fire Bullet and Inflict Damage on the hit object
	OnFire(FollowCamera);

	//Spawn the Particle Effect of the Gun
	SpawnParticleEffects();

	//Spawn Sound And Noise
	SpawnGunShotSound(ShooterCharacter, PawnNoiseEmitter);

	//Alert the AI Characters that a bullet has been fired
	PawnNoiseEmitter->MakeNoise(ShooterCharacter, NoiseVolume, ShooterCharacter->GetActorLocation());

}

void AM4A_Base::ReloadGun_Implementation()
{
	Reload();	//Call the base Reload function that alll guns will implement;
	//Add a custom function for this Gun here
}
