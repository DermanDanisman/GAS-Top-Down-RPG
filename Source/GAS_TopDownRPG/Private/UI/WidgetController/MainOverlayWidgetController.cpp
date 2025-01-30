// Copyright Heathrow


#include "UI/WidgetController/MainOverlayWidgetController.h"

#include "AbilitySystem/GASPAttributeSet.h"

void UMainOverlayWidgetController::BroadcastInitialValues()
{
	ensureMsgf(AttributeSet, TEXT("AttributeSet is nullptr in Main Overlay Widget Controller -> BroadcastInitialValues"));
	const UGASPAttributeSet* GASPAttributeSet = Cast<UGASPAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(GASPAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(GASPAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(GASPAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(GASPAttributeSet->GetMaxMana());
	OnStaminaChanged.Broadcast(GASPAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(GASPAttributeSet->GetMaxStamina());
}

void UMainOverlayWidgetController::RegisterAttributeChangeCallbacks()
{
	/**
	 * Super call: Registers a callback function to listen for attribute changes. 
	 * It uses AddLambda, which is a more flexible and inline way of defining callback functions.
	 */
	Super::RegisterAttributeChangeCallbacks();
	
	const UGASPAttributeSet* GASPAttributeSet = Cast<UGASPAttributeSet>(AttributeSet);

	// Bound HealthChanged to GetGameplayAttributeValueChangeDelegate delegate 
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GASPAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::HealthChanged);

	// Bound MaxHealthChanged to GetGameplayAttributeValueChangeDelegate delegate 
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GASPAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::MaxHealthChanged);

	// Bound ManaChanged to GetGameplayAttributeValueChangeDelegate delegate 
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GASPAttributeSet->GetManaAttribute()).AddUObject(this, &ThisClass::ManaChanged);

	// Bound MaxManaChanged to GetGameplayAttributeValueChangeDelegate delegate 
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GASPAttributeSet->GetMaxManaAttribute()).AddUObject(this, &ThisClass::MaxManaChanged);
}

void UMainOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UMainOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UMainOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UMainOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
