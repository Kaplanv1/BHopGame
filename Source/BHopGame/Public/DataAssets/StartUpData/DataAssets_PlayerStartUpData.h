// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAssets_StartUpDataBase.h"
#include "BHopTypes/BHopStructTypes.h"
#include "DataAssets_PlayerStartUpData.generated.h"

UCLASS()
class BHOPGAME_API UDataAssets_PlayerStartUpData : public UDataAssets_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UBHopAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1)override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty="InputTag"))
	TArray<FBHopPlayerAbilitySet> PlayerStartUpAbilitySets;
	
};
