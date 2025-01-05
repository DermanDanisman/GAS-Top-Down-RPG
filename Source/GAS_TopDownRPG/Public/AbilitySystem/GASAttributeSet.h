// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GASAttributeSet.generated.h"

/**
  * Attributes:
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

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GAS_TOPDOWNRPG_API UGASAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UGASAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;


	UFUNCTION()
	void OnRep_HealthChanged(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealthChanged(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	void OnRep_ManaChanged(const FGameplayAttributeData& OldMana);
	UFUNCTION()
	void OnRep_MaxManaChanged(const FGameplayAttributeData& OldMaxMana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthChanged, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealthChanged, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaChanged, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxManaChanged, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
};
