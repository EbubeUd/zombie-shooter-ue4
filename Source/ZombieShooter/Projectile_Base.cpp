// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile_Base.h"


// Sets default values
AProjectile_Base::AProjectile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set up the Root Component
	//Create the Capsule Static Mesh of the Projectile
	CapsuleStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("CapsuleStaticMesh");
	CapsuleStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule"));
	CapsuleStaticMeshComponent->SetCollisionProfileName(TEXT("CustomOverlap"));
	CapsuleStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	if (CapsuleStaticMesh) CapsuleStaticMeshComponent->SetStaticMesh(CapsuleStaticMesh);
	CapsuleStaticMeshComponent->SetupAttachment(RootComponent);
	CapsuleStaticMeshComponent->SetRelativeScale3D(FVector(.05f, .08f, .05f));
	CapsuleStaticMeshComponent->SetGenerateOverlapEvents(true);
	//Set up the Projectile Movement
	ProjectileMovementComp = CreateDefaultSubobject <UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComp->InitialSpeed = 2000.f;	//Sets the Initial Speed at which the Projectile will leave the muzzle.
	ProjectileMovementComp->MaxSpeed = 2000.f;	//Sets the Max accelerating Speed of the Projectile. 
	ProjectileMovementComp->ProjectileGravityScale = .06f;	//Sets the Gravity acting on the projjectile (The Lesser the Value, the More Force of Gravity is applied on it.)
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = false;


	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void AProjectile_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

