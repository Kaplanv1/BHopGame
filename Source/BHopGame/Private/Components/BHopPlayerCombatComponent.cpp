// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BHopPlayerCombatComponent.h"
#include "Items/Weapons/BHopPlayerMeleeWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Gameplay/Tags/BHopGameplayTags.h"
#include "BHopDebugHelper.h"

ABHopPlayerMeleeWeapon* UBHopPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	return Cast<ABHopPlayerMeleeWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTagToGet));
}

ABHopPlayerMeleeWeapon* UBHopPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
	return Cast<ABHopPlayerMeleeWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UBHopPlayerCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UBHopPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(),BHopGameplayTags::Shared_Event_MeleeHit, Data);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		BHopGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
}

void UBHopPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	/*UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		BHopGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);*/
}
