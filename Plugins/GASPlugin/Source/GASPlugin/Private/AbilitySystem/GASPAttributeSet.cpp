// Copyright Heathrow


#include "AbilitySystem/GASPAttributeSet.h"

#include "Net/UnrealNetwork.h"

UGASPAttributeSet::UGASPAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(10.f);
	InitMaxMana(100.f);
	InitStamina(25.f);
	InitMaxStamina(50.f);
}

void UGASPAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/**
	 * DOREPLIFETIME_CONDITION_NOTIFY: This macro ensures that the attributes will be replicated when necessary, and it allows you to specify replication conditions.
	 * COND_None: This condition means the attribute is always replicated (there’s no special condition like COND_InitialOnly or COND_OwnerOnly).
	 * REPNOTIFY_Always: This ensures that the OnRep_* function is called every time the value changes.
	 * It triggers the relevant notification function regardless of whether the value changed on the server or client.
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, HealthRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, ManaRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, StaminaRegenRate, COND_None, REPNOTIFY_Always);
}

void UGASPAttributeSet::OnRep_HealthChanged(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, Health, OldHealth);
}

void UGASPAttributeSet::OnRep_MaxHealthChanged(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, MaxHealth, OldMaxHealth);
}

void UGASPAttributeSet::OnRep_HealthRegenRateChanged(const FGameplayAttributeData& OldHealthRegenRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, HealthRegenRate, OldHealthRegenRate);
}

void UGASPAttributeSet::OnRep_ManaChanged(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, Mana, OldMana);
}

void UGASPAttributeSet::OnRep_MaxManaChanged(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, MaxMana, OldMaxMana);
}

void UGASPAttributeSet::OnRep_ManaRegenRateChanged(const FGameplayAttributeData& OldManaRegenRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, ManaRegenRate, OldManaRegenRate);
}

void UGASPAttributeSet::OnRep_StaminaChanged(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, Stamina, OldStamina);
}

void UGASPAttributeSet::OnRep_MaxStaminaChanged(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, MaxStamina, OldMaxStamina);
}

void UGASPAttributeSet::OnRep_StaminaRegenRateChanged(const FGameplayAttributeData& OldStaminaRegenRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, StaminaRegenRate, OldStaminaRegenRate);
}
