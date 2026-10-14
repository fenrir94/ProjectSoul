// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpBase.generated.h"

class USoulGameplayAbility;
class USoulAbilitySystemComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class SOUL_API UDataAsset_StartUpBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(USoulAbilitySystemComponent* InASCToGive, int32 Applylevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<USoulGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<USoulGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffect;

	void GrantAbilities(const TArray<TSubclassOf<USoulGameplayAbility>>& InAbilitiesToGive, USoulAbilitySystemComponent* InASCToGive, int32 Applylevel = 1);
};
