//  Copyright 2020 - Infinity DrawnzerGames, Inc. All Rights Reserved.

#include "OnlineFriendsWrapAPI.h"
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
