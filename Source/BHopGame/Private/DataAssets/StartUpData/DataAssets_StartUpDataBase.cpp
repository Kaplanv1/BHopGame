// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAssets_StartUpDataBase.h"
#include "Components/BHopAbilitySystemComponent.h"
#include "Gameplay/Abilities/BHopGameplayAbility.h"


void UDataAssets_StartUpDataBase::GiveToAbilitySystemComponent(UBHopAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf < UGameplayEffect >& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass) continue;

			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();

			InASCToGive->ApplyGameplayEffectToSelf(
				EffectCDO,
				ApplyLevel,
				InASCToGive->MakeEffectContext()
			);
		}
	}

}

void UDataAssets_StartUpDataBase::GrantAbilities(TArray<TSubclassOf<UBHopGameplayAbility>>& InAbilitiesToGive, UBHopAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UBHopGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue; 

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor(); // Set the source object to the avatar actor of the ASC	
		AbilitySpec.Level = ApplyLevel; // Set the level of the ability spec to the given level

		InASCToGive->GiveAbility(AbilitySpec);

	}

}

