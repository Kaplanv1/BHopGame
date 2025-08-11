// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/BHopPlayerAnimInstance.h"
#include "Characters/BHopBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"



void UBHopPlayerAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ABHopBaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
	else
	{
		OwningMovementComponent = nullptr;

	}
}

void UBHopPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{

	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}
