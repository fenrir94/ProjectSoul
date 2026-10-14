// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_Dash.generated.h"

class ACharacter;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDashFinishedDelegate);

UCLASS()
class SOUL_API UAbilityTask_Dash : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FDashFinishedDelegate OnFinished;

	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY()
	float Duration = 1.f;

	UPROPERTY()
	FVector DashDirection;

	UPROPERTY()
	float DashSpeed = 2000;

	UPROPERTY()
	float CapsuleRadius;

	UPROPERTY()
	float CapsuleHalfHeight;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta=(DisplayName="Dash", HidePin="OwningAbility", DefaultToSelf="OwningAbility"))
	static UAbilityTask_Dash* CreateDashTask(UGameplayAbility* OwningAbility, float InDuration, FVector InDirection, float InSpeed, float InCapsuleRadius, float InCapsuleHalfHeight);

	// ~ Begin UGameplayTask Interface
	virtual void TickTask(float DeltaTime) override;
	// ~ End UGameplayTask Interface

	virtual void Activate() override;

private:
	float ElapsedTime = 0.f;

	bool CheckWall(FVector InStart, FVector InDestin);
	bool GetFloorZ(FVector CheckPosition, float& OutFootZ);
};
