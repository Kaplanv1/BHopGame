// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/BHopEnemyGameplayAbility.h"
#include "Characters/BHopEnemyCharacter.h"
#include "Components/EnemyCombatComponent.h"

ABHopEnemyCharacter* UBHopEnemyGameplayAbility::GetEnemyCharacterFromActorInfo() 
{
	if (!CachedBHopEnemyCharacter.IsValid())
	{
		CachedBHopEnemyCharacter = Cast<ABHopEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedBHopEnemyCharacter.IsValid() ? CachedBHopEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UBHopEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo() 
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
