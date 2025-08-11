// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Abilities/BHopGameplayAbility.h"
#include "BHopEnemyGameplayAbility.generated.h"

class ABHopEnemyCharacter;
class UEnemyCombatComponent;


UCLASS()
class BHOPGAME_API UBHopEnemyGameplayAbility : public UBHopGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "BHop|Ability")
	ABHopEnemyCharacter* GetEnemyCharacterFromActorInfo() ;

	UFUNCTION(BlueprintPure, Category = "BHop|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo() ;

private:
	TWeakObjectPtr<ABHopEnemyCharacter> CachedBHopEnemyCharacter;



	
};
