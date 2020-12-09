//  Copyright 2020 - Infinity DrawnzerGames, Inc. All Rights Reserved.

#include "OnlineIdentityWrapAPI.h"
#include "OnlineSubsystem.h"

UOnlineIdentityWrapAPI_Login* UOnlineIdentityWrapAPI_Login::Login(FName OSSToUse, int LocalUserNum, const FOnlineIdentityWrap_OnlineAccountCredentials& OnlineAccountCredentials)
{
	UOnlineIdentityWrapAPI_Login* OnlineIdentityWrapAPI = NewObject<UOnlineIdentityWrapAPI_Login>(GetTransientPackage(), NAME_None);
	if (!OSSToUse.ToString().IsEmpty())
	{
		OnlineIdentityWrapAPI->OSSToUse = OSSToUse;
	}
	OnlineIdentityWrapAPI->LocalUserNum = LocalUserNum;
	OnlineIdentityWrapAPI->AccountCredentials.Id = OnlineAccountCredentials.Id;
	OnlineIdentityWrapAPI->AccountCredentials.Token = OnlineAccountCredentials.Token;
	OnlineIdentityWrapAPI->AccountCredentials.Type = OnlineAccountCredentials.Type;
	return OnlineIdentityWrapAPI;
}

void UOnlineIdentityWrapAPI_Login::Activate()
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get(OSSToUse);
	if (OSS)
	{
		const auto Identity = OSS->GetIdentityInterface().Get();
		if (Identity)
		{
			const TWeakObjectPtr<UOnlineIdentityWrapAPI_Login> WeakThis(this);
			Identity->OnLoginCompleteDelegates->AddLambda([WeakThis, Identity](int LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
			{
				if (const auto Outer = WeakThis.Get())
				{
					if (bWasSuccessful)
					{
						FString Message = "Login Complete, User id = ";
                        Message.Append(Identity->GetUniquePlayerId(LocalUserNum).Get()->ToString());
						Outer->OnLoginResponse.Broadcast(bWasSuccessful, Message);
					}
					else if (bWasSuccessful == false && Error == "Already logged in")
					{
						FString Message = "Already logged in, User id = ";
						Message.Append(Identity->GetUniquePlayerId(LocalUserNum).Get()->ToString());
						Outer->OnLoginResponse.Broadcast(true, Message);
					}
					else
					{
						//Todo -> Handle error conditions more generously.
						Outer->OnLoginResponse.Broadcast(bWasSuccessful, Error);
					}
					Identity->OnLoginCompleteDelegates->RemoveAll(WeakThis.Get());
					Identity->OnLoginCompleteDelegates->Clear();
				}
			});
			Identity->Login(LocalUserNum, AccountCredentials);
		}
	}
}
