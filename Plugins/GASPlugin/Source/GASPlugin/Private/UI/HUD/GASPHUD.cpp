// Copyright Heathrow


#include "UI/HUD/GASPHUD.h"

#include "UI/WidgetController/GASPWidgetController.h"

UGASPWidgetController* AGASPHUD::GetMainOverlayWidgetController(
	const FGASPWidgetControllerData& InWidgetControllerData)
{
	// Ensure that the WidgetControllerClass is set before attempting to create the WidgetController.
	// This prevents attempts to create the controller without a valid class reference.
	ensureMsgf(MainOverlayWidgetControllerClass, TEXT("WidgetControllerClass is uninitialized. It must be set before use."));
	
	// If the WidgetController has not been created, instantiate it using the WidgetControllerClass 
	// and initialize it with the provided data.
	if (MainOverlayWidgetController == nullptr)
	{
		// Create the WidgetController instance using the specified class reference
		MainOverlayWidgetController = NewObject<UGASPWidgetController>(this, MainOverlayWidgetControllerClass);
		
		// Initialize the WidgetController with the provided data (FGASPWidgetControllerData)
		MainOverlayWidgetController->SetWidgetControllerData(InWidgetControllerData);

		// Return the newly created WidgetController
		return MainOverlayWidgetController;
	}

	// If the WidgetController already exists, return the existing instance to avoid duplication
	// The caller will likely cast this return value to the appropriate subclass of UGASPWidgetController
	return MainOverlayWidgetController;
}
