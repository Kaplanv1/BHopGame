// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/BHopPlayerLinkedAnimLayer.h"
#include "AnimInstances/Hero/BHopHeroAnimInstance.h"

UBHopHeroAnimInstance* UBHopPlayerLinkedAnimLayer::GetHeroAnimInstance() const
{
    return Cast<UBHopHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
