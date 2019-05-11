// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkpoint.h"


// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the Box Collision Component
	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	BoxCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::TriggerEnter);
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	ZombieShooterGameMode = Cast<AZombieShooterGameMode>(UGameplayStatics::GetGameMode(this));
}

void ACheckpoint::TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	AZombieShooterCharacter* MainCharacterInstance = Cast<AZombieShooterCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));	//Cast to the Main Character
	if (!MainCharacterInstance) return;	//It means it did not collide with thr Third Person Character
	MainCharacterInstance->ObjectiveText = CheckPointMessage;	//Display the Check point Message
	MainCharacterInstance->Health = 1.f;	//Give the player Full health. (optional)

}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

