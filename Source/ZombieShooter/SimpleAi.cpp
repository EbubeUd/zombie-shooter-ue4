// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleAi.h"


// Sets default values
ASimpleAi::ASimpleAi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 1.f;
	MovementRadius = 250.f;
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASimpleAi::TriggerEnter);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	//Define the Pawn Sensing Component
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");
	PawnSensingComp->SightRadius = 2000.f;
	PawnSensingComp->SetPeripheralVisionAngle(45.f);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASimpleAi::OnSeePawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &ASimpleAi::OnHearNoise);
}

// Called when the game starts or when spawned
void ASimpleAi::BeginPlay()
{
	Super::BeginPlay();

	bCanTakeDamage = true;
	MainCharacter = Cast<AZombieShooterCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//Set Up the AI Controller
	AICtrl = Cast<AAIController>(GetController());

	//The Character Should Start Wandering about at intervals
	GetWorldTimerManager().SetTimer(CharacterMovementTimerHandle, this, &ASimpleAi::MoveCharacterAround, 3.f, true, 0.f);

}


void ASimpleAi::OnHearNoise(APawn * OtherActor, const FVector & Location, float Volume)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I hear you"));
}


void ASimpleAi::OnSeePawn(APawn * OtherPawn)
{
	bCanSeePlayer = true;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("I see you"));
	AICtrl->MoveTo(MainCharacter->GetActorLocation());
}

void ASimpleAi::MoveCharacterAround()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Moving Around"));

	if (PawnSensingComp->CouldSeePawn(MainCharacter)) return;	//Return if the AI character can see the Pawn. It means the AI Must be chasing the pawn
	FVector RandomLocation (0);
	bool MoveStatus =  UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, GetActorLocation(), RandomLocation, MovementRadius);
	if (MoveStatus) {
		AICtrl->MoveTo(RandomLocation);
	}

	
}

// Called every frame
void ASimpleAi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASimpleAi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASimpleAi::TriggerEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Check the Object that Collided with the AI Character
	AProjectile_Base* ProjectileBullet = Cast<AProjectile_Base>(OtherActor);
	if (!ProjectileBullet) return;	//It means the AI Character did not collide with a bullet

	//Spawn the Hit Marker Widget
	MainCharacter->HitMarkerWidget = CreateWidget<UUserWidget>(GetGameInstance(), MainCharacter->HitMarkerWidgetTemplate);
	MainCharacter->HitMarkerWidget->AddToViewport();

	//Prevent the character from taking further Damage while he is taking damage.
	if (!bCanTakeDamage) return;
	bCanTakeDamage = false;	

	//Subtract the Health from the AI Character
	float Damage = MainCharacter->AK47Weapon->GetDamage();
	Health -= Damage;

	//Check if the Character is left with any more health
	if (Health < 0.01f) {
		Die();
	}
	else {
		bCanTakeDamage = true;
		AICtrl->MoveTo(MainCharacter->GetActorLocation());	//Move the Enemy to the location of the Pawn Sooting him
	}
}

void ASimpleAi::Die() 
{
	MainCharacter->ShowKillFeed(Name);
	Destroy();
}

void ASimpleAi::TriggerHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, TEXT("I have been hit"));

}


void ASimpleAi::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	//clear ALL timers that belong to this (Actor) instance.
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}