// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleAi.h"


// Sets default values
ASimpleAi::ASimpleAi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 1.f;
	MovementRadius = 250.f;
	Gravity = 500.f;

	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));
	//Set up the Hand Collision 
	HandCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionOnHand"));
	HandCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASimpleAi::InflictDamageonPlayer);
	HandCollisionComp->SetupAttachment(GetMesh(), TEXT("AttackHand"));
	HandCollisionComp->SetRelativeScale3D(FVector(0.6f, 0.18f, 0.19f));

	//Define the Pawn Sensing Component
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");
	PawnSensingComp->SightRadius = 2000.f;
	PawnSensingComp->SetPeripheralVisionAngle(45.f);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASimpleAi::OnSeePawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &ASimpleAi::OnHearNoise);

	//Set up the Audio
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	GrowlSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/ThirdPersonCPP/Audio/Zombie.Zombie"));
	AudioComp->SetSound(GrowlSound);
	AudioComp->AttenuationOverrides.bAttenuate = true;
	AudioComp->AttenuationOverrides.FalloffDistance = 1700.f;
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
	if (bIsDead) return;
	AICtrl->MoveTo(MainCharacter->GetActorLocation());
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I hear you"));
}


void ASimpleAi::OnSeePawn(APawn * OtherPawn)
{
	if (bIsDead) return;
	bCanSeePlayer = true;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("I see you"));
	AICtrl->MoveTo(MainCharacter->GetActorLocation());
	bAttacking = true;
}

void ASimpleAi::MoveCharacterAround()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Moving Around"));
	if (bIsDead) return;	//Exit if the Enemy is dead
	if (PawnSensingComp->CouldSeePawn(MainCharacter))
	{
		MainCharacter->bIsRecievingDamage = true;
		return;	//Return if the AI character can see the Pawn. It means the AI Must be chasing the pawn
	}
	bAttacking = false;
	MainCharacter->bIsRecievingDamage = false;
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
	GetMovementComponent()->Velocity += Gravity * FVector(0.f, 0.f, -1.f);

}

// Called to bind functionality to input
void ASimpleAi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



void ASimpleAi::Die() 
{
	MainCharacter->ShowKillFeed(Name);
	//GetMesh()->SetAllBodiesPhysicsBlendWeight(100.f, true);
	GetMesh()->SetSimulatePhysics(true);
	
	bIsDead = true;

	//GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ASimpleAi::CompleteDeath, 1.f, true, 3.f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);	//Stop Events from triggering whenever Objects overlap with this Character
	HandCollisionComp->SetGenerateOverlapEvents(false);	//Stop Events From Triggering whenever objects overlap the poisionous Hand of this Character
}

void ASimpleAi::CompleteDeath()
{
	Destroy();
}


void ASimpleAi::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	//clear ALL timers that belong to this (Actor) instance.
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}


void ASimpleAi::InflictDamageonPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, TEXT("I Am Hitting Player"));
	if (bIsDead) return;
	AZombieShooterCharacter* MainCharacter = Cast<AZombieShooterCharacter>(OtherActor);
	if (!MainCharacter) return;
	MainCharacter->TakeDamage();
}

void ASimpleAi::TakeBulletDamage_Implementation(float Damage)
{
	if (bIsDead) return;
	AudioComp->Play();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, TEXT("I have been hit"));
	MainCharacter->HitMarkerWidget = CreateWidget<UUserWidget>(GetGameInstance(), MainCharacter->HitMarkerWidgetTemplate);
	MainCharacter->HitMarkerWidget->AddToViewport();

	//Prevent the character from taking further Damage while he is taking damage.
	if (!bCanTakeDamage) return;
	bCanTakeDamage = false;

	//Subtract the Health from the AI Character
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

void ASimpleAi::TakeFireDamage_Implementation()
{
	if (bIsDead) return;
	AudioComp->Play();
	Health -= 0.1f;
	if (Health < 0.01f) Die();
}
