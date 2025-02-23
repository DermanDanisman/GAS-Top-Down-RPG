// Copyright Heathrow


#include "UI/WidgetController/MainOverlayWidgetController.h"

#include "AbilitySystem/GASPAttributeSet.h"

void UMainOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
}

void UMainOverlayWidgetController::RegisterAttributeChangeCallbacks()
{
	/**
	 * Super call: Registers a callback function to listen for attribute changes. 
	 * It uses AddLambda, which is a more flexible and inline way of defining callback functions.
	 */
	Super::RegisterAttributeChangeCallbacks();
}

