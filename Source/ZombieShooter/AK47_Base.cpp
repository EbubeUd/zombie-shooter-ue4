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

// Called every frame
void AAK47_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void AAK47_Base::Reload()
{
	int Requestedbullets = ClipSize - Ammo;	//Gets the total number of bullets needed by the shooter;
	if (MaxAmmo > Requestedbullets)
	{
		//Subtract the Value of the Bullets requested from the Max ammo and Add to the Ammo
		MaxAmmo -= Requestedbullets;
		Ammo += Requestedbullets;
	}
	else 
	{
		//If the Max Ammo is not up to the number of requested bullets, Just credit the Ammo with the Number of bullets in the Max ammo
		MaxAmmo = 0;
		Ammo += MaxAmmo;
	}
}

