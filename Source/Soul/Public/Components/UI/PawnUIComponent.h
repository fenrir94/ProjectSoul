// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnePercentChangedDelegate, float, NewPercent);


/**
 * 
 */
UCLASS()
class SOUL_API UPawnUIComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnePercentChangedDelegate OnCurrentHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnePercentChangedDelegate OnCurrentStaminaChanged;

	UPROPERTY(BlueprintAssignable)
	FOnePercentChangedDelegate OnCurrentEnergyChanged;

	UPROPERTY(BlueprintAssignable)
	FOnePercentChangedDelegate OnCurrentGuardGaugeChanged;
};
