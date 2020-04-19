// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/Engine.h"
#include "UnrealNetwork.h"
#include "Online.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "ServerRowWidget.h"
#include "MainMenuWidget.h"
#include "Classes/Kismet/KismetTextLibrary.h"
#include "UObject/CoreOnline.h"
#include "ZombieShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API UZombieShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UZombieShooterGameInstance(const FObjectInitializer& ObjectInitializer);

	IOnlineSubsystem*   OnlineSub;

	IOnlineSessionPtr SessionInterface;


	/**
	*	Function to host a game!
	*
	*	@Param		UserID			User that started the request
	*	@Param		SessionName		Name of the Session
	*	@Param		bIsLAN			Is this is LAN Game?
	*	@Param		bIsPresence		"Is the Session to create a presence Session"
	*	@Param		MaxNumPlayers	        Number of Maximum allowed players on this "Session" (Server)
	*/
	bool HostSession( FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);


	/**
	*	Find an online session
	*
	*	@param UserId user that initiated the request
	*	@param bIsLAN are we searching LAN matches
	*	@param bIsPresence are we searching presence sessions
	*/
	void FindSessions( bool bIsLAN, bool bIsPresence);

	/**
	*	Joins a session via a search result
	*
	*	@param SessionName name of session
	*	@param SearchResult Session to join
	*
	*	@return bool true if successful, false otherwise
	*/
	bool JoinSession( FName SessionName, const FOnlineSessionSearchResult& SearchResult);


	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;




	/**
	*	Function fired when a session create request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/**
	*	Function fired when a session start request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	/**
	*	Delegate fired when a session search query has completed
	*
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnFindSessionsComplete(bool bWasSuccessful);

	/**
	*	Delegate fired when a session join request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);


	/**
	*	Delegate fired when a destroying an online session has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);




	//////////////////////////////////////////////////////////////////////////   BLUEPRINT CALLABLE FUNCTIONS	//////////////////////////////////////////////////////////////////////////

	/** Starting an Online Game */
	UFUNCTION(BlueprintCallable, Category = "Network|Test")
		void StartOnlineGame();

	/** Searching and finding a session */
	UFUNCTION(BlueprintCallable, Category = "Network|Test")
		void FindOnlineGames();

	/** Join Online Game */
	UFUNCTION(BlueprintCallable, Category = "Network|Test")
		void JoinOnlineGame(int index);

	/** Destroying Session Link */
	UFUNCTION(BlueprintCallable, Category = "Network|Test")
		void DestroySessionAndLeaveGame();



	//Damage Effect Widgetj
	UPROPERTY()
		UMainMenuWidget *MainMenu;

	UPROPERTY()
		TSubclassOf<UMainMenuWidget> MainMenuTemplate;


	UPROPERTY()
		UPanelWidget* ServerRow;

	UPROPERTY()
		TSubclassOf<UServerRowWidget> ServerRowTemplate;

	public:

		/** Init Function For the Game Instance */
		UFUNCTION(BlueprintCallable)
			void OnInit(UMainMenuWidget* MenuWidgetInstance);

};
