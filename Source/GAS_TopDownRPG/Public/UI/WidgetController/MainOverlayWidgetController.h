// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "UI/WidgetController/GASPWidgetController.h"
#include "MainOverlayWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, Mana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, MaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChangedSignature, float, Stamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxStaminaChangedSignature, float, MaxStamina);

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

	// Delegates to notify the UI when each attribute changes
	UPROPERTY(BlueprintAssignable, Category = "GASP Plugin | Widget Controller | Delegates")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GASP Plugin | Widget Controller | Delegates")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GASP Plugin | Widget Controller | Delegates")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GASP Plugin | Widget Controller | Delegates")
	FOnMaxManaChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GASP Plugin | Widget Controller | Delegates")
	FOnStaminaChangedSignature OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GASP Plugin | Widget Controller | Delegates")
	FOnMaxStaminaChangedSignature OnMaxStaminaChanged;

protected:
	
	/** Callback when Health attribute changes */
	void HealthChanged(const FOnAttributeChangeData& Data) const;

	/** Callback when MaxHealth attribute changes */
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
};
