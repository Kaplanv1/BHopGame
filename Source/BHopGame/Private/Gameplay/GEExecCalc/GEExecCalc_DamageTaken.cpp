// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "Gameplay/BHopAttributeSet.h"
#include "Gameplay/Tags/BHopGameplayTags.h"

struct FBHopDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FBHopDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBHopAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBHopAttributeSet, DamageTaken, Target, false)
	}
};


static const FBHopDamageCapture& GetBHopDamageCapture()
{
	static FBHopDamageCapture BHopDamageCapture;
	return BHopDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/*Slow way of doing capture*/
//FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
//	UWarriorAttributeSet::StaticClass(),
//	GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet,AttackPower)
//);

//FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
//	AttackPowerProperty,
//	EGameplayEffectAttributeCaptureSource::Source,
//	false
//);

//RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

	RelevantAttributesToCapture.Add(GetBHopDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetBHopDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	//EffectSpec.GetContext().GetSourceObject();
	//EffectSpec.GetContext().GetAbility();
	//EffectSpec.GetContext().GetInstigator();
	//EffectSpec.GetContext().GetEffectCauser();
	

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetBHopDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	float BaseDamage = 0.f;
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(BHopGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			break;
		}
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower;

	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetBHopDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
}
