// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BHopAbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h" 
#include "GameplayTagContainer.h"
#include "Gameplay/Abilities/BHopPlayerGameplayAbility.h"

UBHopAbilitySystemComponent::UBHopAbilitySystemComponent()
{
    
    SetIsReplicated(true);
    ReplicationMode = EGameplayEffectReplicationMode::Mixed;
}

void UBHopAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
    if (!InInputTag.IsValid())
    {
        return;
    }

    for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        
        if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))continue;
       
        TryActivateAbility(AbilitySpec.Handle);
	}

}

void UBHopAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}

void UBHopAbilitySystemComponent::GrantPlayerWeaponAbilities(const TArray<FBHopPlayerAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
    if (InDefaultWeaponAbilities.IsEmpty())
    {
        return;
    }

    for (const FBHopPlayerAbilitySet& AbilitySet : InDefaultWeaponAbilities)
    {
        if (!AbilitySet.IsValid())
        {
            continue;
        }
        FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
        AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

        OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}


}

void UBHopAbilitySystemComponent::RemovePlayerWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
    if(InSpecHandlesToRemove.IsEmpty())
    {
        return;
	}

    for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
    {
        if (SpecHandle.IsValid())
        {
			ClearAbility(SpecHandle);
        }
        
    }
    InSpecHandlesToRemove.Empty();

}


