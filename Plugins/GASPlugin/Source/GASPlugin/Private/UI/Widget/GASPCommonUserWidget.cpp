// Copyright Heathrow


#include "UI/Widget/GASPCommonUserWidget.h"

void UGASPCommonUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerIsSet();
}