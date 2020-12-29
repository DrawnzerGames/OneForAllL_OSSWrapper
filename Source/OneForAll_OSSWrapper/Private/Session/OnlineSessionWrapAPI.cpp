//  Copyright 2020 - Infinity DrawnzerGames, Inc. All Rights Reserved.

#include "Session/OnlineSessionWrapAPI.h"
#include "OneForAllOSSTypes.h"
#include "OnlineSessionInterface.h"
#include "OnlineSubsystem.h"

UOnlineSessionWrapAPI_CreateSession* UOnlineSessionWrapAPI_CreateSession::CreateSession(FName OSSToUse, int32 HostingPlayerNum, FName SessionName, const FOnlineSessionWrap_OnlineSessionSettings OnlineSessionSettings)
{
	UOnlineSessionWrapAPI_CreateSession* CreateSession = NewObject<UOnlineSessionWrapAPI_CreateSession>(GetTransientPackage(), NAME_None);
	if (!OSSToUse.ToString().IsEmpty())
	{
		CreateSession->OSSToUse = OSSToUse;
	}
	CreateSession->HostingPlayerNum = HostingPlayerNum;
	CreateSession->PlayerId = "";
	CreateSession->SessionName = SessionName;
	CreateSession->SessionSettings = ConvertSettings(OnlineSessionSettings);
	return CreateSession;
}

UOnlineSessionWrapAPI_CreateSession* UOnlineSessionWrapAPI_CreateSession::CreateSessionFromPlayerId(FName OSSToUse, FString PlayerId, FName SessionName, const FOnlineSessionWrap_OnlineSessionSettings OnlineSessionSettings)
{
	UOnlineSessionWrapAPI_CreateSession* CreateSession = NewObject<UOnlineSessionWrapAPI_CreateSession>(GetTransientPackage(), NAME_None);
	if (!OSSToUse.ToString().IsEmpty())
	{
		CreateSession->OSSToUse = OSSToUse;
	}
	CreateSession->HostingPlayerNum = -1;
	CreateSession->PlayerId = PlayerId;
	CreateSession->SessionName = SessionName;
	CreateSession->SessionSettings = ConvertSettings(OnlineSessionSettings);
	return CreateSession;
}

void UOnlineSessionWrapAPI_CreateSession::Activate()
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get(OSSToUse);
	bool Result = false;
	if (OSS)
	{
		const auto SessionInterface = OSS->GetSessionInterface().Get();
		if (SessionInterface)
		{
			if (HostingPlayerNum == -1)
			{
				Result = SessionInterface->CreateSession(FUniqueNetIdOneForAll(PlayerId, OSSToUse), SessionName, SessionSettings);
			}
			else
			{
				Result = SessionInterface->CreateSession(HostingPlayerNum, SessionName, SessionSettings);
			}
		}
	}
	CreateSessionResponse.Broadcast(Result);
}

FOnlineSessionSettings UOnlineSessionWrapAPI_CreateSession::ConvertSettings(FOnlineSessionWrap_OnlineSessionSettings OnlineSessionSettings)
{
	FOnlineSessionSettings Session = {};
	Session.NumPublicConnections = OnlineSessionSettings.NumPrivateConnections;
	Session.NumPrivateConnections = OnlineSessionSettings.NumPrivateConnections;
	Session.bShouldAdvertise = OnlineSessionSettings.bShouldAdvertise;
	Session.bAllowJoinInProgress = OnlineSessionSettings.bAllowJoinInProgress;
	Session.bIsLANMatch = OnlineSessionSettings.bIsLANMatch;
	Session.bIsDedicated = OnlineSessionSettings.bIsDedicated;
	Session.bUsesStats = OnlineSessionSettings.bUsesStats;
	Session.bAllowInvites = OnlineSessionSettings.bAllowInvites;
	Session.bUsesPresence = OnlineSessionSettings.bUsesPresence;
	Session.bAllowJoinViaPresence = OnlineSessionSettings.bAllowJoinViaPresence;
	Session.bAllowJoinViaPresenceFriendsOnly = OnlineSessionSettings.bAllowJoinViaPresenceFriendsOnly;
	Session.bAntiCheatProtected = OnlineSessionSettings.bAntiCheatProtected;
	Session.BuildUniqueId = OnlineSessionSettings.BuildUniqueId;
	return Session;
}
