// All Rights Reserved.


#include "AbilitySystem/Abilities/HeroGameplayAbility.h"
#include "Characters/HeroCharacter.h"
#include "Controllers/HeroController.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "SoulGameplayTags.h"

AHeroCharacter* UHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!CachedHeroCharacter.IsValid())
    {
        CachedHeroCharacter = Cast<AHeroCharacter>(CurrentActorInfo->AvatarActor);
    }
    return CachedHeroCharacter.IsValid() ? CachedHeroCharacter.Get() : nullptr;
}

AHeroController* UHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (!CachedHeroController.IsValid())
    {
        CachedHeroController = Cast<AHeroController>(CurrentActorInfo->PlayerController);
    }
    return CachedHeroController.IsValid() ? CachedHeroController.Get() : nullptr;
}

UHeroCombatComponent* UHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

USoulTargetLockComponent* UHeroGameplayAbility::GetHeroTargetLockComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetTargetLockComponent();
}

UCineCameraComponent* UHeroGameplayAbility::GetHeroCineCameraFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetCineCamera();
}

UCameraComponent* UHeroGameplayAbility::GetFollowCameraFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetFollowCamera();
}

FGameplayEffectSpecHandle UHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScaleableFloat)
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

FGameplayEffectSpecHandle UHeroGameplayAbility::MakeHeroLifeStealEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InLifeStealPercent)
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
        SoulGameplayTags::Shared_SetByCaller_Steal_Health,
        InLifeStealPercent.GetValueAtLevel(GetAbilityLevel())
    );


    return EffectSpecHandle;
}
