// Fill out your copyright notice in the Description page of Project Settings.


#include "BHopFunctionLibrary.h"
#include <AbilitySystemBlueprintLibrary.h>
#include "Components/BHopAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"

UBHopAbilitySystemComponent* UBHopFunctionLibrary::NativeGetBhopASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UBHopAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
	
}

void UBHopFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
    UBHopAbilitySystemComponent* ASC = NativeGetBhopASCFromActor(InActor);

    if (!ASC->HasMatchingGameplayTag(TagToAdd))
    {
        ASC->AddLooseGameplayTag(TagToAdd);
    }
}

void UBHopFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
    UBHopAbilitySystemComponent* ASC = NativeGetBhopASCFromActor(InActor);

    if (ASC->HasMatchingGameplayTag(TagToRemove))
    {
        ASC->RemoveLooseGameplayTag(TagToRemove);
    }
}

bool UBHopFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
    UBHopAbilitySystemComponent* ASC = NativeGetBhopASCFromActor(InActor);

    return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UBHopFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EBHopConfirmType& OutConfirmType)
{
    OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EBHopConfirmType::Yes : EBHopConfirmType::No;

}

UPawnCombatComponent* UBHopFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
   check(InActor);
   if(IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
   {
       return PawnCombatInterface->GetPawnCombatComponent();
   }
    
   return nullptr;
}


UPawnCombatComponent* UBHopFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EBHopValidType& OutValidType)
{
    UPawnCombatComponent* PawnCombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = PawnCombatComponent ? EBHopValidType::Valid : EBHopValidType::Invalid;

	return PawnCombatComponent;

}