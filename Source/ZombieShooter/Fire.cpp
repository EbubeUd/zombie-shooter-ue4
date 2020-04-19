// Fill out your copyright notice in the Description page of Project Settings.

#include "Fire.h"


// Sets default values
AFire::AFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Up the Root Component
	StaticMeshRootComp = CreateDefaultSubobject<UStaticMeshComponent>("RootComponent");
	SetRootComponent(StaticMeshRootComp);

	//Create the Fire Particle 
	ParticleSysytemComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleSystem = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleSystem) ParticleSysytemComp->SetTemplate(ParticleSystem);
	ParticleSysytemComp->SetupAttachment(StaticMeshRootComp);

	//Set Up the Sound
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	FireSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/StarterContent/Audio/Fire01.Fire01"));
	AudioComp->SetSound(FireSound);
	AudioComp->AttenuationOverrides.bAttenuate = true;
	AudioComp->AttenuationOverrides.FalloffDistance = 1700.f;
	AudioComp->SetupAttachment(StaticMeshRootComp);
	AudioComp->SetRelativeLocation(FVector(0.f));

	//Set up the Collision
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("SphereComponent");
	CapsuleComp->SetRelativeScale3D(FVector(3.f));
	CapsuleComp->SetupAttachment(StaticMeshRootComp);
	CapsuleComp->SetGenerateOverlapEvents(true);
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AFire::InflictDamage);

	
}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();
	AudioComp->Play();
	bCanInflictDamage = true;
}

void AFire::InflictDamage(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (!bCanInflictDamage) return;	//Exit if the fire can not inflict damage.
	

	IDamageable* BurningObjectInterface = Cast<IDamageable>(OtherActor);
	if (!BurningObjectInterface) return;
	if (!bCanInflictDamage) return;	//Exit if the fire can not inflict damage.	(Do this Again to prevent events that entered while the current one was processing)
	bCanInflictDamage = false;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I am Burning"));
	BurningObjectInterface->Execute_TakeFireDamage(OtherActor);
	GetWorldTimerManager().SetTimer(BurnTimer, this, &AFire::ResetCanInflictDamage, 1.f, true, 0.f);

}

void AFire::ResetCanInflictDamage()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I have Set it to true"));
	bCanInflictDamage = true;
	GetWorld()->GetTimerManager().ClearTimer(BurnTimer);
}

// Called every frame
void AFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

