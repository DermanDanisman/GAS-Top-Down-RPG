// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "UI/WidgetController/GASPWidgetController.h"
#include "MainOverlayWidgetController.generated.h"

/**
 * UMainOverlayWidgetController is responsible for controlling the overlay UI for the player.
 * It manages broadcasting the initial values for attributes and handling attribute changes.
 * It inherits from UGASPWidgetController to use the player data and attribute systems.
 */
UCLASS(BlueprintType, Blueprintable)
class GAS_TOPDOWNRPG_API UMainOverlayWidgetController : public UGASPWidgetController
{
	GENERATED_BODY()

public:

	/** 
	 * Broadcasts the initial values for health, mana, stamina, etc., to update the UI.
	 * This function is used when the widget controller is first initialized.
	 */
	virtual void BroadcastInitialValues() override;

	/** 
	 * Registers the callbacks for attribute changes (Health, Mana, etc.).
	 * This function will listen for any changes in the player's attributes and trigger UI updates accordingly.
	 */
	virtual void RegisterAttributeChangeCallbacks() override;
	
};
