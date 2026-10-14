// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SoulFunctionLibrary.h"
#include "SoulGameplayAbility.generated.h"

class USoulAbilitySystemComponent;
class UPawnCombatComponent;

UENUM(BlueprintType)
enum class ESoulAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class SOUL_API USoulGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	

protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	UPROPERTY(EditDefaultsOnly, Category = "SoulAbility")
	ESoulAbilityActivationPolicy AbilityActivationPolicy = ESoulAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	USoulAbilitySystemComponent* GetSoulAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Soul|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExes = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ESoulSuccessType& OutSuccessType);

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	FGameplayEffectSpecHandle MakeSoulSetByCallerEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FGameplayTag& SetByCallerTag, const FScalableFloat& Value);

};
