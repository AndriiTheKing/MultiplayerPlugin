#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

namespace EOnJoinSessionCompleteResult
{
	enum Type : int;
}

class UMultiplayerSessionsSubsystem;
class UButton;

UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(Category = "Menu", BlueprintCallable)
	void MenuSetup(int32 NumberOfConnections = 4, FString TypeOfMatch = TEXT("FreeForAll"), FString LobbyPath = FString("/Game/ThirdPerson/Maps/Lobby"));

	virtual bool Initialize() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;



	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();
	

	void MenuTearDown();

protected:
	virtual void NativeDestruct() override;
	virtual void NativeConstruct() override;

	/*
	 *	Callbacks for the custom dlegates on the MultiplayerSessionsSubsystem
	 */
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful);
	
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);

	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
	
private:
	// The Subsystem designed to handle all online session functionality
	UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	int32 NumPublicConnections = 4;
	FString MatchType = TEXT("FreeForAll");

	FString PathToLobby = TEXT("");

};
