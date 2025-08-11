// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BHopBaseCharacter.h"
#include "BHopEnemyCharacter.generated.h"

class UEnemyCombatComponent;

UCLASS()
class BHOPGAME_API ABHopEnemyCharacter : public ABHopBaseCharacter
{
	GENERATED_BODY()

public:
	ABHopEnemyCharacter();

protected:	

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	// IPawnCombatInterface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

private:
	void InitEnemyStartUpData();


public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent;  }

};
