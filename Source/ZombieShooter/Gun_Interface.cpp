// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun_Interface.h"



void IGun_Interface::OnFire(UCameraComponent* FollowCamera)
{
	//Get the Child Object and Check if it is valid
	UObject* ChildObject = _getUObject();
	if (!ChildObject) return;

	//Get the world and check if it exists
	UWorld* const World = ChildObject->GetWorld();
	if (!World) return;

	//Subtract from the Ammo
	Ammo--;	

	//spawn the line trace from the camera to the targeted location
	FCollisionResponseParams ResponseParams;
	FHitResult OutHit;
	FVector StartLocation = FollowCamera->GetComponentLocation();
	FVector ForwardVector = FollowCamera->GetComponentRotation().Vector() * MaxDistanceBulletCanTravel;
	FVector EndLocation = ForwardVector + StartLocation;
	FCollisionQueryParams CollisionParams;
	//DrawDebugLine(World, StartLocation, EndLocation, FColor::Green, true, 1, 0, 1);
	bool trace = World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams, ResponseParams);
	
	if (trace)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%s"), *OutHit.GetActor()->GetName()));
		if (&OutHit) 
		{
			//Cast The OutHit To An IDamageable interface and if it is not null, call the TakeBulletDamage Function
			AActor* DamageableObject = OutHit.GetActor();
			if (!DamageableObject) return;
			IDamageable* DamageableObjectInterface = Cast<IDamageable>(DamageableObject);
			if (DamageableObjectInterface) IDamageable::Execute_TakeBulletDamage(DamageableObject, Damage);
		}
	}
		
	
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

void IGun_Interface::IncrementMaxAmmo()
{
	 MaxAmmo += ClipSize; 
}




