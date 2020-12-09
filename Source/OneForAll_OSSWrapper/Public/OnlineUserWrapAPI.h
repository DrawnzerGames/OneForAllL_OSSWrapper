//  Copyright 2020 - Infinity DrawnzerGames, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "OnlineUserWrapAPI.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------- THE GET USER INFO API---------------------------------------------------------//

USTRUCT(BlueprintType)
struct FOnlineUserWrap_OnlineUser
{
	GENERATED_BODY()

	/** The id associated with this user. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineUserWrap")
	FString UserId;

	/** The real name. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineUserWrap")
	FText RealName;

	/** The display name. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OneForAllOSSWrapper|OnlineUserWrap")
	FText DisplayName;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetUserInfoResponse, const FOnlineUserWrap_OnlineUser&, UserInfo);

UCLASS()
class ONEFORALL_OSSWRAPPER_API UOnlineUserWrapAPI_GetUserInfo : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category="OneForAllOSSWrapper|OnlineUserWrap")
	FGetUserInfoResponse UserResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName="One For All Get User Info", BlueprintInternalUseOnly = "true"),Category="OneForAllOSSWrapper|OnlineUserWrap")
	static UOnlineUserWrapAPI_GetUserInfo* GetUserInfo(FName OSSToUse, int LocalUserNum, const FString& UserId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName="One For All Get Self User Info", BlueprintInternalUseOnly = "true"),Category="OneForAllOSSWrapper|OnlineUserWrap")
	static UOnlineUserWrapAPI_GetUserInfo* GetSelfUserInfo(FName OSSToUse, int LocalUserNum);

	virtual void Activate() override;

private:
	FName OSSToUse = "EOS";
	int LocalUserNum;
	FString UserId;
};
