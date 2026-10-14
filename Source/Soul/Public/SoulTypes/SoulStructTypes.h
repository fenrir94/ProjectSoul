// All Rights Reserved.

#pragma once

#include "ScalableFloat.h"
#include "SoulStructTypes.generated.h"

class UHeroGameplayAbiliy;

USTRUCT(BlueprintType)
struct FSoulWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;

};