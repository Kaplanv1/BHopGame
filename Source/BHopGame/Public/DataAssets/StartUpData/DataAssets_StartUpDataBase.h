// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAssets_StartUpDataBase.generated.h"

class UBHopAbilitySystemComponent;
class UBHopGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class BHOPGAME_API UDataAssets_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UBHopAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf< UBHopGameplayAbility > > ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf< UBHopGameplayAbility > > ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < UGameplayEffect > > StartUpGameplayEffects;

	void GrantAbilities(TArray<TSubclassOf< UBHopGameplayAbility > >& InAbilitiesToGive, UBHopAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	
};
