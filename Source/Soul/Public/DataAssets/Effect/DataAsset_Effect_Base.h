// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_Effect_Base.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FHitEffectEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag EffectTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName AttackSocket = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector LocationOffset = FVector::ZeroVector;
};


UCLASS(BlueprintType)
class SOUL_API UDataAsset_Effect_Base : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FHitEffectEntry> Effects;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool FindEffectByTag(FGameplayTag InTag, FHitEffectEntry& OutEffect) const;

};
