// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "SoulTargetLockComponent.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetChanged, AActor*, NewTarget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetLost);

UCLASS()
class SOUL_API USoulTargetLockComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	USoulTargetLockComponent();

	UPROPERTY(BlueprintReadOnly)
	AActor* CurrentTarget;

	UPROPERTY(BlueprintAssignable)
	FOnTargetChanged OnTargetChanged;

	UPROPERTY(BlueprintAssignable)
	FOnTargetLost OnTargetLost;

	void EnableTargetLock();
	void DisableTargetLock();

	void SwitchTarget(bool bNext);
	void BroadcastTargetLost();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

private:
	void FindAvailableTargets();
	AActor* GetNearestTarget() const;

	bool bLockEnabled;

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	float MaxLockDistance;

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	FVector BoxTraceExtent;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	TArray<AActor*> AvailableTargets;

	UPROPERTY()
	class USoulWidgetBase* TargetLockWidget;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	TSubclassOf<class USoulWidgetBase> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	float RotationInterpSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	float TargetLockCameraOffsetDistance = 20.f;


	FVector2D TargetLockWidgetSize;

	void UpdateTargetLockWidget();
	void ClearTargetLockWidget();
	void UpdateCameraRotation(float DeltaTime);

};
