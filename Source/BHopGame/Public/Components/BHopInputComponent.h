// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"

#include "BHopInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class BHOPGAME_API UBHopInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserObject, typename CallBackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject ContextObject, CallBackFunc Func);

	template<class UserObject, typename CallBackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject ContextObject, CallBackFunc InputPressedFunc, CallBackFunc InputRelasedFunc);


};

template<class UserObject, typename CallBackFunc>
inline void UBHopInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject ContextObject, CallBackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null ,can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template<class UserObject, typename CallBackFunc>
inline void UBHopInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject ContextObject, CallBackFunc InputPressedFunc, CallBackFunc InputRelasedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null ,can not proceed with binding"));

	for (const FBHopInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid())continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputRelasedFunc, AbilityInputActionConfig.InputTag);
	}

}