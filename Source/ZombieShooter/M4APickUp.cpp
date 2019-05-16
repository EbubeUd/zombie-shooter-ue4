// Fill out your copyright notice in the Description page of Project Settings.

#include "M4APickUp.h"


// Sets default values
AM4APickUp::AM4APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set up the Sphere collision Component
	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxCollisionComp->SetWorldScale3D(FVector(.3f, 1.6f, .3f));
	BoxCollisionComp->SetGenerateOverlapEvents(true);
	BoxCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AM4APickUp::TriggerEnter);
	SetRootComponent(BoxCollisionComp);

	//Set up the skeletal Mesh Component
	SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/ThirdPersonCPP/Blueprints/Weapons/M4A/M4A1.M4A1_weapon002"));
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComp->SkeletalMesh = SkeletalMesh;
	SkeletalMeshComp->SetAbsolute(false, false, true);	//Make the Scale to be independent of the parent Scale
	//SkeletalMeshComp->SetRelativeScale3D(FVector(3.f));
	SkeletalMeshComp->AttachTo(BoxCollisionComp);
	FVector Rot = SkeletalMeshComp->GetComponentLocation();
	SkeletalMeshComp->SetRelativeLocation(FVector(28.f, -24.f, 40.f));
	}

// Called when the game starts or when spawned
void AM4APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}


void AM4APickUp::TriggerEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bHasBeenPicked) return;	//Exit if the collision has already begun
	bHasBeenPicked = true;
	
	AZombieShooterCharacter* MainCharacter = Cast<AZombieShooterCharacter>(OtherActor);
	if (!MainCharacter) 
	{
		//If it was not the Main Actor That Collided with the Pickup, Exit.
		bHasBeenPicked = false;
		return;
	}
	else 
	{	
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Picked M4A"));
		
		MainCharacter->bHasPickedM4A = true;
		MainCharacter->FPSHudWidget->PlayAnimation(MainCharacter->FPSHudWidget->M4APickUpAnimation);
		USoundBase* PickupSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/ThirdPersonCPP/Audio/reload.reload"));
		UGameplayStatics::PlaySound2D(MainCharacter, PickupSound);
		Destroy();
	}


}

// Called every frame
void AM4APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Spin the Gun 
	FRotator ActorRotation = GetActorRotation();
	ActorRotation.Yaw += 0.6f;
	SetActorRotation(ActorRotation);
}

