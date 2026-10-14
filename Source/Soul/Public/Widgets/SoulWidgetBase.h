// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoulWidgetBase.generated.h"

class UHeroUIComponent;
class UEnemyUIComponent;

/**
 * 
 */
UCLASS()
class SOUL_API USoulWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (Display ="On Owning Hero UI Component Initialized"))
	void BP_OnOwningHeroUIComponentInitialized(UHeroUIComponent* OwningHeroUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (Display = "On Owning Enemy UI Component Initialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedwidget(AActor* OwningEnemyActor);
};
