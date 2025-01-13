// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/GASPWidgetController.h"
#include "MainOverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, Mana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, MaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChangedSignature, float, Stamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxStaminaChangedSignature, float, MaxStamina);

/**
 * 
 */
UCLASS()
class GAS_TOPDOWNRPG_API UMainOverlayWidgetController : public UGASPWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadcastInitialValues() override;

	// Delegates
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
};
