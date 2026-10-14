// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SoulGameplayAbility.h"
#include "EnemyGameplayAbility.generated.h"

class AEnemyCharacter;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class SOUL_API UEnemyGameplayAbility : public USoulGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	AEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Soul|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScaleableFloat);

	virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override;

	/** Get "body" of task's owner / default, having location in world (e.g. Owner = AIController, Avatar = Pawn) */
	virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override;
private:
	TWeakObjectPtr<AEnemyCharacter> CachedEnemyCharacter;

};
