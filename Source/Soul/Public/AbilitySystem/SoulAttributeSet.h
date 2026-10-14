// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "SoulAttributeSet.generated.h"

class IPawnUIInterface;

/**
 * 
 */
UCLASS()
class SOUL_API USoulAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
public:
	USoulAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Heath")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Heath")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, CurrentStamina)

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, MaxStamina)

	UPROPERTY(BlueprintReadOnly, Category = "Energy")
	FGameplayAttributeData CurrentEnergy;
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, CurrentEnergy)

	UPROPERTY(BlueprintReadOnly, Category = "Energy")
	FGameplayAttributeData MaxEnergy;
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, MaxEnergy)

	UPROPERTY(BlueprintReadOnly, Category = "GuardGauge")
	FGameplayAttributeData CurrentGuardGauge;
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, CurrentGuardGauge)

	UPROPERTY(BlueprintReadOnly, Category = "GuardGauge")
	FGameplayAttributeData MaxGuardGauge;
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, MaxGuardGauge)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, DamageTaken)

private:
	TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;
};
