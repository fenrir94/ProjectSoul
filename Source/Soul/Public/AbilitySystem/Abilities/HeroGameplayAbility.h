// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SoulGameplayAbility.h"
#include "HeroGameplayAbility.generated.h"

class AHeroCharacter;
class AHeroController;
class UCameraComponent;
class UCineCameraComponent;
class USoulTargetLockComponent;
/**
 * 
 */
UCLASS()
class SOUL_API UHeroGameplayAbility : public USoulGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	AHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	AHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	USoulTargetLockComponent* GetHeroTargetLockComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	UCineCameraComponent* GetHeroCineCameraFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	UCameraComponent* GetFollowCameraFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScaleableFloat);

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	FGameplayEffectSpecHandle MakeHeroLifeStealEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InLifeStealPercent);



private:
	TWeakObjectPtr<AHeroCharacter> CachedHeroCharacter;
	TWeakObjectPtr<AHeroController> CachedHeroController;
};
