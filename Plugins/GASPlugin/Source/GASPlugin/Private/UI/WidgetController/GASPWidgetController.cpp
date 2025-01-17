// Copyright Heathrow


#include "UI/WidgetController/GASPWidgetController.h"

void UGASPWidgetController::SetWidgetControllerData(const FGASPWidgetControllerData& InWidgetControllerData)
{
	PlayerController = InWidgetControllerData.PlayerController;
	PlayerState = InWidgetControllerData.PlayerState;
	AbilitySystemComponent = InWidgetControllerData.AbilitySystemComponent;
	AttributeSet = InWidgetControllerData.AttributeSet;
}

void UGASPWidgetController::BroadcastInitialValues()
{
	
}

void UGASPWidgetController::RegisterAttributeChangeCallbacks()
{
	
}
