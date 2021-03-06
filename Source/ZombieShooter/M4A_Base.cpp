// Fill out your copyright notice in the Description page of Project Settings.

#include "M4A_Base.h"


// Sets default values
AM4A_Base::AM4A_Base()
	:Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Emitter
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	FlashEmitter = PS.Object;
}

// Called when the game starts or when spawned
void AM4A_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AM4A_Base::SpawnParticleEffects()
{
	//Spawn Emitter
	FlashEmitterComponent = UGameplayStatics::SpawnEmitterAtLocation(this, FlashEmitter, WeaponSkeletalMesh->GetSocketLocation("Muzzle"));
	FlashEmitterComponent->SetWorldScale3D(FVector(.05f, .05f, .05f));
}

void AM4A_Base::SpawnGunShotSound(AActor * ShooterCharacter, UPawnNoiseEmitterComponent * PawnNoiseEmitter)
{
	if (FireSound == nullptr) return;

	//Spawn a GunShot 
	UGameplayStatics::PlaySound2D(this, FireSound, .5f);

	//Make A Noise So the AI Characters Can be alerted
	PawnNoiseEmitter->MakeNoise(ShooterCharacter, NoiseVolume, ShooterCharacter->GetActorLocation());
}

void AM4A_Base::Fire(UCameraComponent* FollowCamera, AActor* ShooterCharacter, UPawnNoiseEmitterComponent *PawnNoiseEmitter)
{
	Super::Fire(FollowCamera, ShooterCharacter, PawnNoiseEmitter);

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

void AM4A_Base::Reload()
{
	Super::Reload();	//Call the base Reload function that alll guns will implement;
}




