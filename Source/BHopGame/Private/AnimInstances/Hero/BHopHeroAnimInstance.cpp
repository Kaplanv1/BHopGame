// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/BHopHeroAnimInstance.h"
#include "Characters/Player/BHopPlayer.h"

void UBHopHeroAnimInstance::NativeInitializeAnimation()
{

	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningPlayer = Cast<ABHopPlayer>(OwningCharacter);
	}
}

void UBHopHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
