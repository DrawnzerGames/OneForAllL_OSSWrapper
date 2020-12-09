//  Copyright 2020 - Infinity DrawnzerGames, Inc. All Rights Reserved.

#include "OnlineUserWrapAPI.h"
#include "OneForAllOSSTypes.h"
#include "OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineUserInterface.h"

UOnlineUserWrapAPI_GetUserInfo* UOnlineUserWrapAPI_GetUserInfo::GetUserInfo(FName OSSToUse, int LocalUserNum, const FString& UserId)
{
	UOnlineUserWrapAPI_GetUserInfo* GetUserInfo = NewObject<UOnlineUserWrapAPI_GetUserInfo>(GetTransientPackage(), NAME_None);
	if (!OSSToUse.ToString().IsEmpty())
	{
		GetUserInfo->OSSToUse = OSSToUse;
	}
	GetUserInfo->LocalUserNum = LocalUserNum;
	GetUserInfo->UserId = UserId;
	return GetUserInfo;
}

UOnlineUserWrapAPI_GetUserInfo* UOnlineUserWrapAPI_GetUserInfo::GetSelfUserInfo(FName OSSToUse, int LocalUserNum)
{
	UOnlineUserWrapAPI_GetUserInfo* GetUserInfo = NewObject<UOnlineUserWrapAPI_GetUserInfo>(GetTransientPackage(), NAME_None);
	if (!OSSToUse.ToString().IsEmpty())
	{
		GetUserInfo->OSSToUse = OSSToUse;
	}
	GetUserInfo->LocalUserNum = LocalUserNum;
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get(OSSToUse);
	if (OSS)
	{
		const auto UserInterface = OSS->GetIdentityInterface().Get();
		if (UserInterface)
		{
			GetUserInfo->UserId = UserInterface->GetUniquePlayerId(LocalUserNum).Get()->ToString();
		}
	}
	return GetUserInfo;
}

void UOnlineUserWrapAPI_GetUserInfo::Activate()
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get(OSSToUse);
	FOnlineUserWrap_OnlineUser User = {};
	if (OSS)
	{
		const auto UserInterface = OSS->GetUserInterface().Get();
		if (UserInterface)
		{
			const auto UserInfo = UserInterface->GetUserInfo(LocalUserNum, FUniqueNetIdOneForAll(UserId, OSSToUse)).Get();
			if (UserInfo)
			{
				User.UserId = UserInfo->GetUserId().Get().ToString();
				User.RealName = FText::FromString(UserInfo->GetRealName());
				User.DisplayName = FText::FromString(UserInfo->GetDisplayName());
			}
		}
	}
	UserResponse.Broadcast(User);
}
