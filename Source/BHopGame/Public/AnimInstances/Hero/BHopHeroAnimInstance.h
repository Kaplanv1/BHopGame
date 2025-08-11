// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/BHopPlayerAnimInstance.h"
#include "BHopHeroAnimInstance.generated.h"


class ABHopPlayer;

UCLASS()
class BHOPGAME_API UBHopHeroAnimInstance : public UBHopPlayerAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	ABHopPlayer* OwningPlayer;

	
};
