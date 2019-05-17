// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun_Interface.h"



void IGun_Interface::OnFire(UCameraComponent* FollowCamera)
{
	if (Ammo < 1)	return;	//Check if there is enough ammo
	Ammo--;	//Reduce the Ammo Count by 1;

	//Spawn Line Trace
	UWorld* const World = GetChildActorReference()->GetWorld();
	if (World) {
		FCollisionResponseParams ResponseParams;
		FHitResult OutHit;
		FVector StartLocation = FollowCamera->GetComponentLocation();
		FVector ForwardVector = FollowCamera->GetComponentRotation().Vector() * MaxDistanceBulletCanTravel;
		FVector EndLocation = ForwardVector + StartLocation;
		FCollisionQueryParams CollisionParams;
		DrawDebugLine(World, StartLocation, EndLocation, FColor::Green, true, 1, 0, 1);
		bool trace = World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams, ResponseParams);
		if (trace)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%s"), *OutHit.GetActor()->GetName()));
			if (&OutHit) 
			{
				//Cast The OutHit To An IDamageable interface and if it is not null, call the TakeBulletDamage Function
				AActor* DamageableObject = OutHit.GetActor();
				if (!DamageableObject) return;
				IDamageable* DamageableObjectInterface = Cast<IDamageable>(DamageableObject);
				if (DamageableObjectInterface) IDamageable::Execute_TakeBulletDamage(DamageableObject, Damage);
			}
		}
		//Deduct the Health From AI Character If He Was Hit
	}
	
	//Spawn Sound
	UGameplayStatics::PlaySound2D(GetChildActorReference(), FireSound, 1.f);

	//Spawn Emitter
	FlashEmitterComponent = UGameplayStatics::SpawnEmitterAtLocation(GetChildActorReference(), FlashEmitter, GetSkeletalMeshComponent()->GetSocketLocation("Muzzle"));
	FlashEmitterComponent->SetWorldScale3D(FVector(.05f, .05f, .05f));
}

void IGun_Interface::Reload()
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


