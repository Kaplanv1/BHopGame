// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BHopPlayerMeleeWeapon.h"

void ABHopPlayerMeleeWeapon::AssignGrantAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> ABHopPlayerMeleeWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
 