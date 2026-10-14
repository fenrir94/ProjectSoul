// All Rights Reserved.


#include "AbilitySystem/Abilities/EnemyGameplayAbility.h"
#include "Characters/EnemyCharacter.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "SoulGameplayTags.h"

#include "DebugHelper.h"

AEnemyCharacter* UEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<AEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScaleableFloat)
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

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		SoulGameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScaleableFloat.GetValueAtLevel(GetAbilityLevel())
	);

	

	return EffectSpecHandle;
}

AActor* UEnemyGameplayAbility::GetGameplayTaskOwner(const UGameplayTask* Task) const
{
	FString Msg = FString::Printf(TEXT("TaskOwner: %s	Task: %s"), *Super::GetGameplayTaskOwner(Task)->GetName(), *Task->GetName());

	Debug::Print(Msg);
	return Super::GetGameplayTaskOwner(Task);
}

AActor* UEnemyGameplayAbility::GetGameplayTaskAvatar(const UGameplayTask* Task) const
{
	FString Msg = FString::Printf(TEXT("TaskAvatar: %s	Task: %s"), *Super::GetGameplayTaskAvatar(Task)->GetName(), *Task->GetName());

	Debug::Print(Msg);

	return Super::GetGameplayTaskAvatar(Task);
}
