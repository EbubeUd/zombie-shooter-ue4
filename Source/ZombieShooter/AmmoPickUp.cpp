// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoPickUp.h"


// Sets default values
AAmmoPickUp::AAmmoPickUp()
{


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshObject(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComp->SetStaticMesh(StaticMeshObject.Object);
	StaticMeshComp->SetWorldScale3D(FVector(.3f));

	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>("BoxCollisionComp");
	BoxCollisionComp->SetWorldScale3D(FVector(.3f));
	BoxCollisionComp->SetWorldLocation(FVector(.0f));
	BoxCollisionComp->SetGenerateOverlapEvents(true);
	BoxCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPickUp::TriggerEnter);

	HasRecievedAmmo = false;

	//StaticMeshComp->SetRelativeLocation(FVector(0.f));
	
	StaticMeshComp->AttachTo(BoxCollisionComp);
}

// Called when the game starts or when spawned
void AAmmoPickUp::BeginPlay()
{
	Super::BeginPlay();

}

void AAmmoPickUp::TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (HasRecievedAmmo) return;
	HasRecievedAmmo = true;
	ShooterCharacter = Cast<AZombieShooterCharacter>(OtherActor);
	if (!ShooterCharacter) return;
	ShooterCharacter->AK47Weapon->IncrementMaxAmmo();

	//Spawn a Pick up sound
	PickupSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/ThirdPersonCPP/Audio/Pick_Up.Pick_Up"));
	UGameplayStatics::PlaySound2D(this, PickupSound, 1.f);
	Destroy();
}

// Called every frame
void AAmmoPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


