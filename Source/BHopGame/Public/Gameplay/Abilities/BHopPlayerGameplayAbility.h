// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Abilities/BHopGameplayAbility.h"
#include "BHopPlayerGameplayAbility.generated.h"


class ABHopPlayer;
class ABHopPlayerController;
class UBHopPlayerCombatComponent;
/**
 * 
 */
UCLASS()
class BHOPGAME_API UBHopPlayerGameplayAbility : public UBHopGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "BHop|Ability")
	ABHopPlayer* GetPlayerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "BHop|Ability")
	ABHopPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "BHop|Ability")
	UBHopPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "BHop|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect>EffectClass,float InWeaponBaseDamage,FGameplayTag InCurrentAttackTypeTag,int32 InUsedComboCount);


private:
	TWeakObjectPtr<ABHopPlayer> CachedPlayer;
	TWeakObjectPtr<ABHopPlayerController> CachedController;



};
