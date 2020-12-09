//  Copyright 2020 - Infinity DrawnzerGames, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineIdentityInterface.h"
#include "OnlineBlueprintCallProxyBase.h"
#include "OnlineIdentityWrapAPI.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------- THE LOGIN API-----------------------------------------------------------------//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLoginResponse, bool, Successful, FString, Message);

USTRUCT(BlueprintType)
struct FOnlineIdentityWrap_OnlineAccountCredentials
{
	GENERATED_BODY()

	/** Type of account. Needed to identity the auth method to use (epic, internal, facebook, etc) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineIdentityWrap")
	FString Type;

	/** Id of the user logging in (email, display name, facebook id, etc) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineIdentityWrap")
	FString Id;
	/** Credentials of the user logging in (password or auth token) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineIdentityWrap")
	FString Token;
};

UCLASS()
class ONEFORALL_OSSWRAPPER_API UOnlineIdentityWrapAPI_Login : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category="OneForAllOSSWrapper|OnlineIdentityWrap")
	FOnLoginResponse OnLoginResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName="One For All Login", BlueprintInternalUseOnly = "true"),Category="OneForAllOSSWrapper|OnlineIdentityWrap")
	static UOnlineIdentityWrapAPI_Login* Login(FName OSSToUse, int LocalUserNum, const FOnlineIdentityWrap_OnlineAccountCredentials& OnlineAccountCredentials);

	virtual void Activate() override;

private:
	FName OSSToUse = "EOS";
	int LocalUserNum;
	FOnlineAccountCredentials AccountCredentials;
};
