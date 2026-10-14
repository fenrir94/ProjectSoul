// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpBase.h"
#include "GameplayTagContainer.h"
#include "DataAsset_HeroStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USoulGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};
/**
 * 
 */
UCLASS()
class SOUL_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(USoulAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FHeroAbilitySet> HeroStartUpAbilitySets;


};
