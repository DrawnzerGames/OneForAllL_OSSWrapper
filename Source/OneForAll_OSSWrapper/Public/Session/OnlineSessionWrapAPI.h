//  Copyright 2020 - Infinity DrawnzerGames, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "OnlineSessionWrapAPI.generated.h"

USTRUCT(BlueprintType)
struct FOnlineSessionWrap_OnlineSessionSettings
{
	GENERATED_BODY()

	/** The number of publicly available connections advertised */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	int32 NumPublicConnections;

	/** The number of connections that are private (invite/password) only */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	int32 NumPrivateConnections;

	/** Whether this match is publicly advertised on the online service */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	bool bShouldAdvertise;

	/** Whether joining in progress is allowed or not */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	bool bAllowJoinInProgress;

	/** This game will be lan only and not be visible to external players */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	bool bIsLANMatch;

	/** Whether the server is dedicated or player hosted */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	bool bIsDedicated;

	/** Whether the match should gather stats or not */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	bool bUsesStats;

	/** Whether the match allows invitations for this session or not */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	bool bAllowInvites;

	/** Whether to display user presence information or not */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	bool bUsesPresence;

	/** Whether joining via player presence is allowed or not */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	bool bAllowJoinViaPresence;

	/** Whether joining via player presence is allowed for friends only or not */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	bool bAllowJoinViaPresenceFriendsOnly;

	/** Whether the server employs anti-cheat (punkbuster, vac, etc) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	bool bAntiCheatProtected;

	/** Used to keep different builds from seeing each other during searches */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	int32 BuildUniqueId;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlineCreateSessionResponse, bool, Successful);

UCLASS()
class ONEFORALL_OSSWRAPPER_API UOnlineSessionWrapAPI_CreateSession : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category="OneForAllOSSWrapper|OnlineSessionWrap")
	FOnlineCreateSessionResponse CreateSessionResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName="One For All Create Session", BlueprintInternalUseOnly = "true"),Category="OneForAllOSSWrapper|OnlineSessionWrap")
	static UOnlineSessionWrapAPI_CreateSession* CreateSession(FName OSSToUse, int32 HostingPlayerNum, FName SessionName, const FOnlineSessionWrap_OnlineSessionSettings OnlineSessionSettings);

	UFUNCTION(BlueprintCallable, meta = (DisplayName="One For All Create Session From Player Id", BlueprintInternalUseOnly = "true"),Category="OneForAllOSSWrapper|OnlineSessionWrap")
	static UOnlineSessionWrapAPI_CreateSession* CreateSessionFromPlayerId(FName OSSToUse, FString PlayerId, FName SessionName, const FOnlineSessionWrap_OnlineSessionSettings OnlineSessionSettings);

	virtual void Activate() override;

private:
	FName OSSToUse = "EOS";
	FName SessionName;
	int HostingPlayerNum;
	FString PlayerId;
	FOnlineSessionSettings SessionSettings;

	static FOnlineSessionSettings ConvertSettings(FOnlineSessionWrap_OnlineSessionSettings OnlineSessionSettings);
};
