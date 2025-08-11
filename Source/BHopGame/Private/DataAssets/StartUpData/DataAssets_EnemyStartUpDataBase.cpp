// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAssets_EnemyStartUpDataBase.h"
#include "Components/BHopAbilitySystemComponent.h"
#include "Gameplay/Abilities/BHopEnemyGameplayAbility.h"

void UDataAssets_EnemyStartUpDataBase::GiveToAbilitySystemComponent(UBHopAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf < UBHopEnemyGameplayAbility >& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}