// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FBHopInputActionConfig& Config : NativeInputActions)
	{
		if (Config.InputTag == InputTag)
		{
			return Config.InputAction;
		}
	}
	return nullptr;
}
