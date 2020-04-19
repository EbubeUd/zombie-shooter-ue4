// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieShooterGameInstance.h"


UZombieShooterGameInstance::UZombieShooterGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	ServerRowTemplate = LoadClass<UServerRowWidget>(nullptr, TEXT("/Game/ThirdPersonCPP/Blueprints/Widgets/ServerRow.ServerRow_C"));
}

void UZombieShooterGameInstance::OnInit(UMainMenuWidget* MenuWidgetInstance)
{
	// Get the Online Subsystem to work with
	OnlineSub = IOnlineSubsystem::Get();

	//Call the Init Function after 2 seconds

	//Get the Sessions Interface
	SessionInterface = OnlineSub->GetSessionInterface();

	/** Bind function for CREATING a Session */
	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UZombieShooterGameInstance::OnCreateSessionComplete);

	/** Bind function for starting a Session */
	SessionInterface->OnStartSessionCompleteDelegates.AddUObject(this, &UZombieShooterGameInstance::OnStartOnlineGameComplete);

	/** Bind function for FINDING a Session */
	SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UZombieShooterGameInstance::OnFindSessionsComplete);

	/** Bind function for JOINING a Session */
	SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UZombieShooterGameInstance::OnJoinSessionComplete);

	/** Bind function for DESTROYING a Session */
	SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UZombieShooterGameInstance::OnDestroySessionComplete);

	/** Assing the Men Widget Instance */
	MainMenu = MenuWidgetInstance;
}




bool UZombieShooterGameInstance::HostSession( FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
	UE_LOG(LogTemp, Warning, TEXT("Beginning to host a Session"));

	//Get the player
	ULocalPlayer* const player = GetFirstGamePlayer();

	//Set the UserId
	const TSharedPtr<const FUniqueNetId> UserId = player->GetPreferredUniqueNetId().GetUniqueNetId();

	// Get the Online Subsystem to work with

	if (OnlineSub)
	{
		
		if (SessionInterface.IsValid() && UserId.IsValid())
		{
			/*
				Fill in all the Session Settings that we want to use.

				There are more with SessionSettings.Set(...);
				For example the Map or the GameMode/Type.
			*/

			DestroySessionAndLeaveGame();

			SessionSettings = MakeShareable(new FOnlineSessionSettings());

			SessionSettings->bIsLANMatch = bIsLAN;
			SessionSettings->bUsesPresence = bIsPresence;
			SessionSettings->NumPublicConnections = MaxNumPlayers;
			SessionSettings->NumPrivateConnections = 0;
			SessionSettings->bAllowInvites = true;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

			SessionSettings->Set(SETTING_MAPNAME, FString("NewMap"), EOnlineDataAdvertisementType::ViaOnlineService);

			

			// Our delegate should get called when this is complete (doesn't need to be successful!)
			return SessionInterface->CreateSession(*UserId, SessionName, *SessionSettings);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No OnlineSubsytem found!"));
	}

	return false;
}

void UZombieShooterGameInstance::FindSessions( bool bIsLAN, bool bIsPresence)
{
	//Get the player
	ULocalPlayer* const player = GetFirstGamePlayer();

	//Set the UserId
	const TSharedPtr<const FUniqueNetId> UserId = player->GetPreferredUniqueNetId().GetUniqueNetId();

	
	UE_LOG(LogTemp, Warning, TEXT("Started Findiing Sessions"));


	//Clear the Search UI
	MainMenu->ServerListScrollBox->ClearChildren();

	//Add Text to Notify User that we are Searching for Sessions
	UServerRowWidget* ServerRowWidg = CreateWidget<UServerRowWidget>(UGameplayStatics::GetGameInstance(this), ServerRowTemplate);
	ServerRowWidg->ServerNameTextBlock->SetText(UKismetTextLibrary::Conv_StringToText("Searching for Servers..."));
	ServerRowWidg->JoinSessionButton->OnClicked.Clear();
	MainMenu->ServerListScrollBox->AddChild(ServerRowWidg);

	if (OnlineSub)
	{

		if (SessionInterface.IsValid() && UserId.IsValid())
		{
			/*
				Fill in all the SearchSettings, like if we are searching for a LAN game and how many results we want to have!
			*/
			SessionSearch = MakeShareable(new FOnlineSessionSearch());

			SessionSearch->bIsLanQuery = bIsLAN;


			// We only want to set this Query Setting if "bIsPresence" is true
			if (bIsPresence)
			{
				SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
			}

			TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();


			// Finally call the SessionInterface function. The Delegate gets called once this is finished
			SessionInterface->FindSessions(*UserId, SearchSettingsRef);

			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Num Search Results: %d"), SessionSearch->SearchResults.Num()));

		}
	}
	else
	{
		// If something goes wrong, just call the Delegate Function directly with "false".
		OnFindSessionsComplete(false);
	}
}

bool UZombieShooterGameInstance::JoinSession( FName SessionName, const FOnlineSessionSearchResult & SearchResult)
{

	//Get the player
	ULocalPlayer* const player = GetFirstGamePlayer();

	//Set the UserId
	const TSharedPtr<const FUniqueNetId> UserId = player->GetPreferredUniqueNetId().GetUniqueNetId();


	// Return bool
	bool bSuccessful = false;

	if (OnlineSub)
	{
		
		if (SessionInterface.IsValid() && UserId.IsValid())
		{
			// Set the Handle again

			// Call the "JoinSession" Function with the passed "SearchResult". The "SessionSearch->SearchResults" can be used to get such a
			// "FOnlineSessionSearchResult" and pass it. Pretty straight forward!
			bSuccessful = SessionInterface->JoinSession(*UserId, SessionName, SearchResult);
		}
	}

	return bSuccessful;
}

void UZombieShooterGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnCreateSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));

	if (OnlineSub)
	{

		if (SessionInterface.IsValid())
		{
			if (bWasSuccessful)
			{
			
				// Our StartSessionComplete delegate should get called after this
				SessionInterface->StartSession(SessionName);
			}
		}

	}
}

void UZombieShooterGameInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnStartSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));



	// If the start was successful, we can open a NewMap if we want. Make sure to use "listen" as a parameter!
	if (bWasSuccessful)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap", true, "listen");
	}
}

void UZombieShooterGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Num Search Results: %d"), SessionSearch->SearchResults.Num()));


	
	if (OnlineSub)
	{
		if (SessionInterface.IsValid())
		{
			
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Valid Session Interface")));

			// Just debugging the Number of Search results. Can be displayed in UMG or something later on
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Num Search Results: %d"), SessionSearch->SearchResults.Num()));

			MainMenu->ServerListScrollBox->ClearChildren();

			// If we have found at least 1 session, we just going to debug them. You could add them to a list of UMG Widgets, like it is done in the BP version!
			if (SessionSearch->SearchResults.Num() > 0)
			{
				// "SessionSearch->SearchResults" is an Array that contains all the information. You can access the Session in this and get a lot of information.
				// This can be customized later on with your own classes to add more information that can be set and displayed
				int index = 0;
				for (FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
				{
					// OwningUserName is just the SessionName for now. I guess you can create your own Host Settings class and GameSession Class and add a proper GameServer Name here.
					// This is something you can't do in Blueprint for example!
					UServerRowWidget* ServerRowWidg = CreateWidget<UServerRowWidget>(UGameplayStatics::GetGameInstance(this), ServerRowTemplate);
					if (!ServerRowWidg) continue;;
					ServerRowWidg->ServerNameTextBlock->SetText(UKismetTextLibrary::Conv_StringToText(SearchResult.GetSessionIdStr()));
					ServerRowWidg->Index = index;
					MainMenu->ServerListScrollBox->AddChild(ServerRowWidg);
					UE_LOG(LogTemp, Warning, TEXT("Found Session Name %s"), *SearchResult.GetSessionIdStr());
					index++;
				}
			}
			else
			{
				UServerRowWidget* ServerRowErrorWidget = CreateWidget<UServerRowWidget>(UGameplayStatics::GetGameInstance(this), ServerRowTemplate);
				ServerRowErrorWidget->ServerNameTextBlock->SetText(UKismetTextLibrary::Conv_StringToText("No Servers found"));
				ServerRowErrorWidget->JoinSessionButton->OnClicked.Clear();
				MainMenu->ServerListScrollBox->AddChild(ServerRowErrorWidget);
			}
		}
	}
}

void UZombieShooterGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnJoinSessionComplete %s, %d"), *SessionName.ToString(), static_cast<int32>(Result)));

	if (OnlineSub)
	{

		if (SessionInterface.IsValid())
		{
			

			// Get the first local PlayerController, so we can call "ClientTravel" to get to the Server Map
			// This is something the Blueprint Node "Join Session" does automatically!
			APlayerController * const PlayerController = GetFirstLocalPlayerController();

			// We need a FString to use ClientTravel and we can let the SessionInterface contruct such a
			// String for us by giving him the SessionName and an empty String. We want to do this, because
			// Every OnlineSubsystem uses different TravelURLs
			FString TravelURL;

			if (PlayerController && SessionInterface->GetResolvedConnectString(SessionName, TravelURL))
			{
				// Finally call the ClienTravel. If you want, you could print the TravelURL to see
				// how it really looks like
				PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);

			}
		}
	}
}

void UZombieShooterGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnDestroySessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));

	if (OnlineSub)
	{
		// Get the SessionInterface from the OnlineSubsystem
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
		
			// If it was successful, we just load another level (could be a MainMenu!)
			if (bWasSuccessful)
			{
				UGameplayStatics::OpenLevel(GetWorld(), "ThirdPersonExampleMap", true);
			}
		}
	}
}

void UZombieShooterGameInstance::StartOnlineGame()
{
	

	// Call our custom HostSession function. GameSessionName is a GameInstance variable
	HostSession(GameSessionName, true, true, 4);
}

void UZombieShooterGameInstance::FindOnlineGames()
{

	FindSessions(true, true);
}

void UZombieShooterGameInstance::JoinOnlineGame(int index)
{
	if (!SessionSearch) return;

	// If the Array is not empty, we can go through it
	if (SessionSearch->SearchResults.Num() > 0)
	{
		JoinSession( GameSessionName, SessionSearch->SearchResults[index]);
	}
}

void UZombieShooterGameInstance::DestroySessionAndLeaveGame()
{
	if (OnlineSub)
	{

		if (SessionInterface.IsValid())
		{

			SessionInterface->DestroySession(GameSessionName);
		}
	}
}




