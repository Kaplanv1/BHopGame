// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/BHopAnimInstanceBase.h"
#include "BHopFunctionLibrary.h"

bool UBHopAnimInstanceBase::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UBHopFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
