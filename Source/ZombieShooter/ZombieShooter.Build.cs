// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ZombieShooter : ModuleRules
{
	public ZombieShooter(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bFasterWithoutUnity = true;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore", "AIModule", "NavigationSystem", "OnlineSubsystem"});

        //if (Target.Platform == UnrealTargetPlatform.Android)
        //{
        //    PrivateDependencyModuleNames.Add("OnlineSubsystemGooglePlay");
        //}

        //For Online Networking
        //DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

            //For LAN Networking
            //DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

            //For Online Networking
            PrivateDependencyModuleNames.Add("OnlineSubsystem");

    }
}
