// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"	
#include "BHopBaseCharacter.generated.h"

class UBHopAbilitySystemComponent;
class UBHopAttributeSet;
class UDataAssets_StartUpDataBase;

UCLASS()
class BHOPGAME_API ABHopBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABHopBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// IPawnCombatInterface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

protected:

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UBHopAbilitySystemComponent* BHopAbilitySystemComponent;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UBHopAttributeSet* BHopAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAssets_StartUpDataBase> CharacterStartUpData;



public:

	FORCEINLINE UBHopAbilitySystemComponent* GetBHopAbilitySystemComponent() const { return BHopAbilitySystemComponent; }
	FORCEINLINE	UBHopAttributeSet* GetBHopAttributeSet() const { return BHopAttributeSet; }


};
