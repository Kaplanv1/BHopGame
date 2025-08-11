// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAssets_StartUpDataBase.h"
#include "DataAssets_EnemyStartUpDataBase.generated.h"

class UBHopEnemyGameplayAbility;

UCLASS()
class BHOPGAME_API UDataAssets_EnemyStartUpDataBase : public UDataAssets_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UBHopAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < UBHopEnemyGameplayAbility > > EnemyCombatAbilities;
	
};
