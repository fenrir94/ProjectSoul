// All Rights Reserved.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/SoulAttributeSet.h"
#include "SoulGameplayTags.h"
#include "GameplayEffectTypes.h"

#include "DebugHelper.h"

struct FSoulDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FSoulDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulAttributeSet, DamageTaken, Target, false)
	}

};

static const FSoulDamageCapture& GetSoulDamageCapture()
{
	static FSoulDamageCapture SoulDamageCapture;
	return SoulDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetSoulDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetSoulDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetSoulDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSoulDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	//Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);

	float BaseDamage = 1.f;
	int32 UsedLightAttackComboCount = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(SoulGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("BaseDamage"), BaseDamage);

		}

		if (TagMagnitude.Key.MatchesTagExact(SoulGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);

		}
	}

	float TargetDefensePower = 0.f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSoulDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	//Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05 + 1.f;

		BaseDamage += DamageIncreasePercentLight;
		//Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage);
	}


	const float FinalDamageDone = BaseDamage * SourceAttackPower - TargetDefensePower;
	//Debug::Print(TEXT("FinalDamage"), FinalDamageDone);

	if (FinalDamageDone > 0.f)
	{

		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetSoulDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}


}
