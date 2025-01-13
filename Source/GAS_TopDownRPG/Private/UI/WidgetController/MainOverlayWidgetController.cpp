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
