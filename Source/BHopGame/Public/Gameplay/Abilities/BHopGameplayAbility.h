// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BHopTypes/BHopEnumTypes.h"
#include "BHopGameplayAbility.generated.h"

class UPawnCombatComponent;
class UBHopAbilitySystemComponent;

UENUM(BlueprintType)
enum class EBHopAbilityActivationPolicy : uint8
{
	OnTriggered UMETA(DisplayName = "On Triggered"),
	OnGiven UMETA(DisplayName = "On Given")
};

UCLASS()
class BHOPGAME_API UBHopGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	// The activation policy for this ability
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BHop|Ability")
	EBHopAbilityActivationPolicy AbilityActivationPolicy = EBHopAbilityActivationPolicy::OnTriggered;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION(BlueprintPure, Category = "BHop|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "BHop|Ability")
	UBHopAbilitySystemComponent* GetBHopAbilitySystemComponentFromActorInfo() const;


	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "BHop|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EBHopSuccessType& OutSuccessType);
};
