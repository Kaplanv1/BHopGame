// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BHopBaseCharacter.h"
#include "Components/BHopAbilitySystemComponent.h"
#include "Gameplay/BHopAttributeSet.h"

// Sets default values
ABHopBaseCharacter::ABHopBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BHopAbilitySystemComponent=CreateDefaultSubobject<UBHopAbilitySystemComponent>(TEXT("BHopAbilitySystemComponent"));
	BHopAttributeSet = CreateDefaultSubobject<UBHopAttributeSet>(TEXT("BHopAttributeSet"));
}

void ABHopBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (BHopAbilitySystemComponent && BHopAttributeSet)
	{
		BHopAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}

}

UAbilitySystemComponent* ABHopBaseCharacter::GetAbilitySystemComponent() const
{
	return GetBHopAbilitySystemComponent();
}

UPawnCombatComponent* ABHopBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}
