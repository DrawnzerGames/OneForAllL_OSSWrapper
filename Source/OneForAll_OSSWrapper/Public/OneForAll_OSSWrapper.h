//  Copyright 2020 - Infinity DrawnzerGames, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FOneForAll_OSSWrapperModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
