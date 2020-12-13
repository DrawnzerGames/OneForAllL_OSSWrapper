//  Copyright 2020 - Infinity DrawnzerGames, Inc. All Rights Reserved.

#include "OnlineFriendsWrapAPI.h"
#include "OneForAllOSSTypes.h"
#include "OnlineFriendsInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineUserInterface.h"

UOnlineFriendsWrapAPI_GetFriendsList* UOnlineFriendsWrapAPI_GetFriendsList::GetFriendsList(FName OSSToUse, int32 LocalUserNum)
{
	UOnlineFriendsWrapAPI_GetFriendsList* GetFriendsList = NewObject<UOnlineFriendsWrapAPI_GetFriendsList>(GetTransientPackage(), NAME_None);
	if (!OSSToUse.ToString().IsEmpty())
	{
		GetFriendsList->OSSToUse = OSSToUse;
	}
	GetFriendsList->LocalUserNum = LocalUserNum;
	return GetFriendsList;
}

void UOnlineFriendsWrapAPI_GetFriendsList::Activate()
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get(OSSToUse);
	TArray<FOnlineFriendWrap_OnlineFriend> OnlineFriends;
	if (OSS)
	{
		const auto FriendsInterface = OSS->GetFriendsInterface().Get();
		const auto UserInterface = OSS->GetUserInterface().Get();
		if (FriendsInterface && UserInterface)
		{
			TArray<TSharedRef<FOnlineFriend>> OutFriends;
			FriendsInterface->GetFriendsList(LocalUserNum, FString(), OutFriends);

			for (const auto Friend : OutFriends)
			{
				const auto FriendUserInfo = UserInterface->GetUserInfo(LocalUserNum, Friend.Get().GetUserId().Get()).Get();
				if (FriendUserInfo)
				{
					FOnlineFriendWrap_OnlineFriend OnlineFriend = {};
					OnlineFriend.UserId = FriendUserInfo->GetUserId().Get().ToString();
					OnlineFriend.RealName = FText::FromString(FriendUserInfo->GetRealName());
					OnlineFriend.DisplayName = FText::FromString(FriendUserInfo->GetDisplayName());
					OnlineFriends.Add(OnlineFriend);
				}
			}
		}
	}
	FriendsListResponse.Broadcast(OnlineFriends);
}

UOnlineFriendsWrapAPI_GetFriend* UOnlineFriendsWrapAPI_GetFriend::GetFriend(FName OSSToUse, int32 LocalUserNum, FString FriendId)
{
	UOnlineFriendsWrapAPI_GetFriend* GetFriend = NewObject<UOnlineFriendsWrapAPI_GetFriend>(GetTransientPackage(), NAME_None);
	if (!OSSToUse.ToString().IsEmpty())
	{
		GetFriend->OSSToUse = OSSToUse;
	}
	GetFriend->LocalUserNum = LocalUserNum;
	GetFriend->FriendId = FriendId;
	return GetFriend;
}

void UOnlineFriendsWrapAPI_GetFriend::Activate()
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get(OSSToUse);
	FOnlineFriendWrap_OnlineFriend Friend = {};
	if (OSS)
	{
		const auto FriendsInterface = OSS->GetFriendsInterface().Get();
		const auto UserInterface = OSS->GetUserInterface().Get();
		if (FriendsInterface && UserInterface)
		{
			const auto RawFriend = FriendsInterface->GetFriend(LocalUserNum, FUniqueNetIdOneForAll(FriendId, OSSToUse), FString()).Get();
			if (RawFriend)
			{
				const auto FriendUserInfo = UserInterface->GetUserInfo(LocalUserNum, RawFriend->GetUserId().Get()).Get();
				if (FriendUserInfo)
				{
					Friend.UserId = FriendUserInfo->GetUserId().Get().ToString();
					Friend.RealName = FText::FromString(FriendUserInfo->GetRealName());
					Friend.DisplayName = FText::FromString(FriendUserInfo->GetDisplayName());
				}
			}
		}
	}
	FriendResponse.Broadcast(Friend);
}
