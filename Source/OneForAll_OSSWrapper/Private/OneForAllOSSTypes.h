//  Copyright 2020 - Infinity DrawnzerGames, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemTypes.h"


class FUniqueNetIdOneForAll : public FUniqueNetIdString
{
public:
	FUniqueNetIdOneForAll() : FUniqueNetIdString()
	{
	}

	explicit FUniqueNetIdOneForAll(const FString& InUniqueNetId, FName OSSType) : FUniqueNetIdString(InUniqueNetId, OSSType)
	{
	}

	friend uint32 GetTypeHash(const FUniqueNetIdOneForAll& A)
	{
		return ::GetTypeHash(A.UniqueNetIdStr);
	}

	static const TSharedRef<const FUniqueNetId>& EmptyId()
	{
		static const TSharedRef<const FUniqueNetId> EmptyId(MakeShared<FUniqueNetIdOneForAll>());
		return EmptyId;
	}
};
