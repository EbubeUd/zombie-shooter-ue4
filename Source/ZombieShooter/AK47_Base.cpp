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


void AAK47_Base::OnFire()
{
	
	if (Ammo < 1)	return;	//Check if there is enough ammo
	Ammo--;	//Reduce the Ammo Count by 1;

	//Spawn the Projectile
	UWorld* const World = GetWorld();
	FTransform MuzzleTransform = WeaponSkeletalMesh->GetSocketTransform(TEXT("Muzzle"));
	World->SpawnActor<AProjectile_Base>(AProjectile_Base::StaticClass(), MuzzleTransform);

	//Spawn Sound
	UGameplayStatics::PlaySound2D(this, FireSound, 1.f);
	
	//Spawn Emitter
	FlashEmitterComponent = UGameplayStatics::SpawnEmitterAtLocation(this, FlashEmitter, WeaponSkeletalMesh->GetSocketLocation("Muzzle"));
	FlashEmitterComponent->SetWorldScale3D(FVector(.05f, .05f, .05f));
}



