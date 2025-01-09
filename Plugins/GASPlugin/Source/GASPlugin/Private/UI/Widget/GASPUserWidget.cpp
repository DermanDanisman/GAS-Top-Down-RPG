// Copyright Heathrow


#include "UI/Widget/GASPUserWidget.h"

void UGASPUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerIsSet();
}

void UGASPUserWidget::WidgetControllerIsSet()
{
}
