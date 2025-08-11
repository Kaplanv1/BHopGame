// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnCombatComponent.h"
#include "BHopPlayerCombatComponent.generated.h"


class ABHopPlayerMeleeWeapon;

UCLASS()
class BHOPGAME_API UBHopPlayerCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Combat")
	ABHopPlayerMeleeWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	ABHopPlayerMeleeWeapon* GetPlayerCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel)const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;

};
