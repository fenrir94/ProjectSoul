// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/HeroGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "HeroGameplayAbility_Dash.generated.h"

/**
 * 
 */
UCLASS()
class SOUL_API UHeroGameplayAbility_Dash : public UHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	// ~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// ~ End UGameplayAbility Interface

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dash")
	float DashSpeed = 900.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float DashDuration = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float DefaultSpeed = 300.f;

	void OnStaminaChanged(const FOnAttributeChangeData& Data);
};
