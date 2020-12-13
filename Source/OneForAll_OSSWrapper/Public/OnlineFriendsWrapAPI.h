//  Copyright 2020 - Infinity DrawnzerGames, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "OnlineFriendsWrapAPI.generated.h"


//-----------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------- THE GET FRIENDS LIST API------------------------------------------------------//

USTRUCT(BlueprintType)
struct FOnlineFriendWrap_OnlineFriend
{
	GENERATED_BODY()

	/** The id associated with this user. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineFriendsWrap")
	FString UserId;

	/** The real name. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineFriendsWrap")
	FText RealName;

	/** The display name. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineFriendsWrap")
	FText DisplayName;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetFriendsListResponse, const TArray<FOnlineFriendWrap_OnlineFriend>&, FriendsList);


UCLASS()
class ONEFORALL_OSSWRAPPER_API UOnlineFriendsWrapAPI_GetFriendsList : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category="OneForAllOSSWrapper|OnlineFriendsWrap")
	FGetFriendsListResponse FriendsListResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName="One For All Get Friends List", BlueprintInternalUseOnly = "true"),Category="OneForAllOSSWrapper|OnlineFriendsWrap")
	static UOnlineFriendsWrapAPI_GetFriendsList* GetFriendsList(FName OSSToUse, int32 LocalUserNum);

	virtual void Activate() override;

private:
	FName OSSToUse = "EOS";
	int LocalUserNum;
};

//-----------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------- THE GET FRIEND API------------------------------------------------------------//

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetFriendResponse, const FOnlineFriendWrap_OnlineFriend&, Friend);

UCLASS()
class ONEFORALL_OSSWRAPPER_API UOnlineFriendsWrapAPI_GetFriend : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category="OneForAllOSSWrapper|OnlineFriendsWrap")
	FGetFriendResponse FriendResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName="One For All Get Friend", BlueprintInternalUseOnly = "true"),Category="OneForAllOSSWrapper|OnlineFriendsWrap")
	static UOnlineFriendsWrapAPI_GetFriend* GetFriend(FName OSSToUse, int32 LocalUserNum, FString FriendId);

	virtual void Activate() override;

private:
	FName OSSToUse = "EOS";
	int LocalUserNum;
	FString FriendId;
};
