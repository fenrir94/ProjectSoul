// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/HeroGameplayAbility.h"
#include "HeroGameplayAbility_TargetLock.generated.h"

class USoulWidgetBase;
/**
 * 
 */
UCLASS()
class SOUL_API UHeroGameplayAbility_TargetLock : public UHeroGameplayAbility
{
	GENERATED_BODY()
	
protected:
	// ~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// ~ End UGameplayAbility Interface

	void OnTargetLost();

	//UFUNCTION(BlueprintCallable)
	//void OnTargetLockTick(float DeltaTime);

//private:
//	void TryLockOnTarget();
//	void GetAvailableActorsToLock();
//	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);
//	void DrawTargetLockWidget();
//	void SetTargetLockWidgetPosition();
//
//	void CancelTargetLockAbility();
//	void CleanUp();
//
//	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
//	float BoxTraceDistance = 5000.f;
//
//	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
//	FVector TraceBoxSize = FVector(5000.f, 5000.f, 300.f);
//
//	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
//	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;
//
//	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
//	float MaxLockDistance = 2000.f;
//
//	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
//	bool bShowPersistentDebugShape = false;
//
//	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
//	TSubclassOf<USoulWidgetBase> TargetLockWidgetClass;
//
//	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
//	float TargetLockRotationInterpSpeed = 5.f;
//
//	UPROPERTY()
//	TArray<AActor*> AvailableActorsToLock;
//
//	UPROPERTY()
//	AActor* CurrentLockedActor;
//
//	UPROPERTY()
//	USoulWidgetBase* DrawnTargetLockWidget;
//	
//	UPROPERTY()
//	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;
};

