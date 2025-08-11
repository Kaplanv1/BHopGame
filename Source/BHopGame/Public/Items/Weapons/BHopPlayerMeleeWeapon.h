// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/BHopMeleeWeaponBase.h"
#include "BHopTypes/BHopStructTypes.h"
#include "GameplayAbilitySpec.h"
#include "BHopPlayerMeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class BHOPGAME_API ABHopPlayerMeleeWeapon : public ABHopMeleeWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FBHopPlayerWeaponData PlayerWeaponData;


	UFUNCTION(BlueprintCallable)
	void AssignGrantAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;



private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;

	
};
