// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class SOUL_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(USoulAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UEnemyGameplayAbility>> EnemyCombatAbilities;

};
