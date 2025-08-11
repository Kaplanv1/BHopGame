// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/BHopAnimInstanceBase.h"
#include "BHopPlayerLinkedAnimLayer.generated.h"


class UBHopHeroAnimInstance;

UCLASS()
class BHOPGAME_API UBHopPlayerLinkedAnimLayer : public UBHopAnimInstanceBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure,meta = (BlueprintThreadSafe))
	UBHopHeroAnimInstance* GetHeroAnimInstance() const;


	
};
