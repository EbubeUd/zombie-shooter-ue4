// Fill out your copyright notice in the Description page of Project Settings.

#include "AK47_Base.h"


// Sets default values
AAK47_Base::AAK47_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set the Properties of the weapon
	FireRate = .1f;
	MaxAmmo = 750;
	ClipSize = 50;
	Ammo = ClipSize;
	Damage = .1f;
	MaxDistanceBulletCanTravel = 1500.f;
	NoiseVolume = .8f;


	//Set the Skeletal Mesh of the Weapon
	SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/ThirdPersonCPP/Blueprints/Weapons/AK47/AK.AK"));
	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponSkeletalMesh");
	if(SkeletalMesh) WeaponSkeletalMesh->SetSkeletalMesh(SkeletalMesh);
	WeaponSkeletalMesh->SetupAttachment(RootComponent);	
	

	//Emitter
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	FlashEmitter = PS.Object;

	
}

// Called when the game starts or when spawned
void AAK47_Base::BeginPlay()
{
	Super::BeginPlay();
	FireSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/ThirdPersonCPP/Audio/Ak.Ak"));
}

void AAK47_Base::SpawnParticleEffects()
{
	//Spawn Emitter
	FlashEmitterComponent = UGameplayStatics::SpawnEmitterAtLocation(this, FlashEmitter, WeaponSkeletalMesh->GetSocketLocation("Muzzle"));
	FlashEmitterComponent->SetWorldScale3D(FVector(.05f, .05f, .05f));
}

void AAK47_Base::SpawnGunShotSound(AActor* ShooterCharacter, UPawnNoiseEmitterComponent* PawnNoiseEmitter)
{
	//Spawn a GunShot 
	UGameplayStatics::PlaySound2D(this, FireSound, .5f);

	//Make A Noise So the AI Characters Can be alerted
	PawnNoiseEmitter->MakeNoise(ShooterCharacter, NoiseVolume, ShooterCharacter->GetActorLocation());
}

void AAK47_Base::FireGun_Implementation(UCameraComponent* FollowCamera, AActor* ShooterCharacter, UPawnNoiseEmitterComponent *PawnNoiseEmitter)
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

void AAK47_Base::ReloadGun_Implementation()
{
	Reload();	//Call the base Reload function that alll guns will implement;
	//Add a custom function for this Gun here
}




