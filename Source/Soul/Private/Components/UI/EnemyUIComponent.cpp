// All Rights Reserved.


#include "Components/UI/EnemyUIComponent.h"
#include "Widgets/SoulWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(USoulWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty())
	{
		return;
	}

	for (USoulWidgetBase* DrawnWidget : EnemyDrawnWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}
}
