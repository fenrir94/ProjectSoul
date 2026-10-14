// All Rights Reserved.


#include "AbilitySystem/Abilities/SoulGameplayAbility.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void USoulGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == ESoulAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && ActorInfo->AbilitySystemComponent.IsValid())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}

}

void USoulGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == ESoulAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* USoulGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

USoulAbilitySystemComponent* USoulGameplayAbility::GetSoulAbilitySystemComponentFromActorInfo() const
{
	return Cast<USoulAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle USoulGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	if (!TargetActor || !InSpecHandle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Target or Effect Spec Handle"));
		return FActiveGameplayEffectHandle();
	}

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC)
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetActor %s has no AbilitySystemComponent"), *TargetActor->GetName());
		return FActiveGameplayEffectHandle();
	}
	//check(TargetASC && InSpecHandle.IsValid());

	return GetSoulAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		TargetASC
	);
}

FActiveGameplayEffectHandle USoulGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ESoulSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? ESoulSuccessType::Successful : ESoulSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}

FGameplayEffectSpecHandle USoulGameplayAbility::MakeSoulSetByCallerEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FGameplayTag& SetByCallerTag, const FScalableFloat& Value)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetSoulAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetSoulAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	if (EffectSpecHandle.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(
			SetByCallerTag,
			Value.GetValueAtLevel(GetAbilityLevel())
		);
	}

	return FGameplayEffectSpecHandle();
}

