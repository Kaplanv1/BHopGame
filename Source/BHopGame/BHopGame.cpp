// Copyright Epic Games, Inc. All Rights Reserved.

#include "BHopGame.h"
#include "Modules/ModuleManager.h"


class FBHopGameModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override
	{
		FDefaultGameModuleImpl::StartupModule();
		
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FBHopGameModule, BHopGame, "BHopGame");
