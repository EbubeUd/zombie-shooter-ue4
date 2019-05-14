// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun_Interface.h"



void IGun_Interface::OnFire()
{
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
