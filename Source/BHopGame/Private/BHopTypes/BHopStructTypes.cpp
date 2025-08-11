// Fill out your copyright notice in the Description page of Project Settings.


#include "BHopTypes/BHopStructTypes.h"
#include "Gameplay/Abilities/BHopPlayerGameplayAbility.h"

bool FBHopPlayerAbilitySet::IsValid() const
{
	return AbilityToGrant && InputTag.IsValid();
}