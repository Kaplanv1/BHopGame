// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "BHopStructTypes.generated.h"

class UBHopPlayerGameplayAbility;
class UInputMappingContext;
class UBHopPlayerLinkedAnimLayer; 


USTRUCT(BlueprintType)
struct FBHopPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Category = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UBHopPlayerGameplayAbility> AbilityToGrant;

	bool IsValid() const;

};

USTRUCT(BlueprintType)
struct FBHopPlayerWeaponData
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBHopPlayerLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty ="InputTag"))
	TArray<FBHopPlayerAbilitySet> DefaultWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	FScalableFloat WeaponBaseDamage;

};