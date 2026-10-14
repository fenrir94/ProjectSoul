// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	LeftWeapon,
	RightWeapon
};

/**
 * 
 */
UCLASS()
class SOUL_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Soul|Combat")
	void ToggleWeaponBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTarget(AActor* InteractedActor);

	TArray<AActor*> OverlappedActors;
};
