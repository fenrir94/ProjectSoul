// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SoulAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class SOUL_API USoulAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);
	
	UFUNCTION(BlueprintCallable, Category = "Soul|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);
};
