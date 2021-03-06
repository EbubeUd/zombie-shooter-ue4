// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Base.h"

// Sets default values
AWeapon_Base::AWeapon_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set the Properties of the weapon
	/*FireRate = .5f;
	MaxAmmo = 750;
	ClipSize = 50;
	Ammo = ClipSize;
	Damage = .1f;
	MaxDistanceBulletCanTravel = 2000.f;
	NoiseVolume = 100.f;*/

	RootComp = CreateDefaultSubobject<USkeletalMeshComponent>("RootComponent");
	SetRootComponent(RootComp);


	//Set the Skeletal Mesh of the Weapon
	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponSkeletalMesh");
	WeaponSkeletalMesh->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bHasBeenPicked)
	{
		FRotator ActorRotation = GetActorRotation();
		ActorRotation.Yaw += 0.6f;
		SetActorRotation(ActorRotation);
	}
}

void AWeapon_Base::Fire(UCameraComponent* FollowCamera, AActor* NoiseMaker, UPawnNoiseEmitterComponent *PawnNoiseEmitter)
{

}


void AWeapon_Base::Reload()
{

}


void AWeapon_Base::OnFire_Implementation(UCameraComponent* FollowCamera)
{

}

void AWeapon_Base::IncrementMaxAmmo(int value)
{
	MaxAmmo += value;
}


void AWeapon_Base::OnEquip_Implementation(AActor* Equipper)
{

}