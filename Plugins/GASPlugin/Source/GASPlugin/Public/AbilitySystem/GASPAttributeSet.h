// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GASPAttributeSet.generated.h"

/**
Attributes:
In Gameplay Ability System (GAS), Attributes and Attribute Sets are essential components that manage and represent various character stats,
such as health, mana, stamina, damage, and more. These attributes can be modified through gameplay effects and are closely tied to abilities and the overall game mechanics.
Attributes have the type FGameplayAttributeData.

FGameplayAttributeData: This is a struct that holds a single value for the attribute (e.g., a float for health).
ATTRIBUTE_ACCESSORS: This is a macro that generates getter and setter functions for each attribute, making it easier to access and modify them.

Summary:
Attributes are the core stats (e.g., health, mana, stamina) that directly impact gameplay.
Attribute Set is a container for the attributes and provides functions to access and modify them.
Gameplay Abilities interact with these attributes, modifying them through Gameplay Effects.
Replication ensures that attribute values are consistent across clients in multiplayer games.
*/

/**
* This defines a set of helper functions for accessing and initializing attributes, to avoid having to manually write these functions.
* It would create the following functions, for attribute Health
*
*	static FGameplayAttribute UMyHealthSet::GetHealthAttribute();
*	FORCEINLINE float UMyHealthSet::GetHealth() const;
*	FORCEINLINE void UMyHealthSet::SetHealth(float NewVal);
*	FORCEINLINE void UMyHealthSet::InitHealth(float NewVal);
*/

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GASPLUGIN_API UGASPAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	UGASPAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;


	/** The OnRep_* functions are callbacks that are executed when the corresponding attribute is updated.
	 * These are useful for triggering any visual or gameplay-related effects that need to happen when an attribute value changes
	 * (e.g., updating a UI element when health changes).
	 */ 
	UFUNCTION()
	void OnRep_HealthChanged(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealthChanged(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_HealthRegenRateChanged(const FGameplayAttributeData& OldHealthRegenRate) const;
	UFUNCTION()
	void OnRep_ManaChanged(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxManaChanged(const FGameplayAttributeData& OldMaxMana) const;
	UFUNCTION()
	void OnRep_ManaRegenRateChanged(const FGameplayAttributeData& OldManaRegenRate) const;
	UFUNCTION()
	void OnRep_StaminaChanged(const FGameplayAttributeData& OldStamina) const;
	UFUNCTION()
	void OnRep_MaxStaminaChanged(const FGameplayAttributeData& OldMaxStamina) const;
	UFUNCTION()
	void OnRep_StaminaRegenRateChanged(const FGameplayAttributeData& OldStaminaRegenRate) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthChanged, Category = "GASP Plugin | Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGASPAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealthChanged, Category = "GASP Plugin | Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGASPAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegenRateChanged, Category = "GASP Plugin | Vital Attributes")
	FGameplayAttributeData HealthRegenRate;
	ATTRIBUTE_ACCESSORS(UGASPAttributeSet, HealthRegenRate);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaChanged, Category = "GASP Plugin | Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UGASPAttributeSet, Mana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxManaChanged, Category = "GASP Plugin | Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UGASPAttributeSet, MaxMana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegenRateChanged, Category = "GASP Plugin | Vital Attributes")
	FGameplayAttributeData ManaRegenRate;
	ATTRIBUTE_ACCESSORS(UGASPAttributeSet, ManaRegenRate);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaChanged, Category = "GASP Plugin | Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UGASPAttributeSet, Stamina);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStaminaChanged, Category = "GASP Plugin | Vital Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UGASPAttributeSet, MaxStamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegenRateChanged, Category = "GASP Plugin | Vital Attributes")
	FGameplayAttributeData StaminaRegenRate;
	ATTRIBUTE_ACCESSORS(UGASPAttributeSet, StaminaRegenRate);

};
