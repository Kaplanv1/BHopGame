// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/BHopPlayerGameplayAbility.h"
#include "Characters/Player/BHopPlayer.h"
#include "Controllers/BHopPlayerController.h"
#include "Components/BHopPlayerCombatComponent.h"
#include "Components/BHopAbilitySystemComponent.h"
#include "Gameplay/Tags/BHopGameplayTags.h"

ABHopPlayer* UBHopPlayerGameplayAbility::GetPlayerFromActorInfo() 
{

	if (!CachedPlayer.IsValid())
	{
		CachedPlayer = Cast<ABHopPlayer>(CurrentActorInfo->AvatarActor);
	}

	return CachedPlayer.IsValid() ? CachedPlayer.Get() : nullptr;
}

ABHopPlayerController* UBHopPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedController.IsValid())
	{
		CachedController = Cast<ABHopPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedController.IsValid() ? CachedController.Get() : nullptr;
}

UBHopPlayerCombatComponent* UBHopPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{

	return GetPlayerFromActorInfo()->GetCombatComponent();
}

FGameplayEffectSpecHandle UBHopPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetBHopAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetBHopAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(BHopGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}
	return EffectSpecHandle;
}
