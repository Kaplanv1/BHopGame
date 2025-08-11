// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAssets_PlayerStartUpData.h"
#include "Gameplay/Abilities/BHopPlayerGameplayAbility.h"
#include "Components/BHopAbilitySystemComponent.h"



void UDataAssets_PlayerStartUpData::GiveToAbilitySystemComponent(UBHopAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FBHopPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid())continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor(); 
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag); // Add the input tag to the dynamic ability tags

		InASCToGive->GiveAbility(AbilitySpec);

	}
}
