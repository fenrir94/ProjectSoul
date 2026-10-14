// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class USoulWidgetBase;
/**
 * 
 */
UCLASS()
class SOUL_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(USoulWidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();

private:
	TArray<USoulWidgetBase*> EnemyDrawnWidgets;
};
