// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleHook_Base.h"

// Sets default values
AGrappleHook_Base::AGrappleHook_Base()
	:Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void AGrappleHook_Base::Fire(UCameraComponent* FollowCamera, AActor* ShooterCharacter, UPawnNoiseEmitterComponent *PawnNoiseEmitter)
{
	Super::Fire(FollowCamera, ShooterCharacter, PawnNoiseEmitter);
	OnFire(FollowCamera);
}

void AGrappleHook_Base::Reload()
{
	Super::Reload();
}


// Called when the game starts or when spawned
void AGrappleHook_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrappleHook_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

