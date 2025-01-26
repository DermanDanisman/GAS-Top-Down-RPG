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

Attributes have 2 protected member variables called BaseValue and Current Value. The BaseValue is the permanent value of an attribute,
while the CurrentValue is the BaseValue plus any temporary modifications caused by GameplayEffects.

Base Value:

	This is the permanent value of an attribute.
	It represents the starting, unmodified value.
	For example, the Base Health is the original health value, without any gameplay effects that temporarily modify it (like buffs or debuffs).
	The Base Value can be modified by permanent effects, such as leveling up, equipment, or permanent buffs.

Current Value:

	This is the value that can fluctuate during gameplay, depending on temporary effects.
	For instance, if a gameplay effect (like a health potion or buff) is applied, it will modify the Current Health without changing the Base Health.
	Current Value is dynamic and can be modified by temporary buffs, debuffs, or in-game actions.
	The Current Value will always be subject to clamping if you want to prevent it from exceeding certain limits (like Max Health).

FGameplayAttributeData: This is a struct that holds a single value for the attribute (e.g., a float for health).
ATTRIBUTE_ACCESSORS: This is a macro that generates getter and setter functions for each attribute, making it easier to access and modify them.

Summary:
Attributes are the core stats (e.g., health, mana, stamina) that directly impact gameplay.
Attribute Set is a container for the attributes and provides functions to access and modify them.
Gameplay Abilities interact with these attributes, modifying them through Gameplay Effects.
Replication ensures that attribute values are consistent across clients in multiplayer games.
*/

/**
* Macro to define getter, setter, and initialization functions for attributes in the attribute set.
* It automatically creates functions to get, set, and initialize attributes, reducing boilerplate code.
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

// Struct to hold actor, controller, and character data for both source and target of gameplay effects.
USTRUCT(BlueprintType)
struct FGameplayEffectProperties
{
	GENERATED_BODY()
	
	/** 
	 * The context handle that contains the effect's context data. It stores information about the effect, such as its origin.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Ability System | Gameplay Effect Properties")
	FGameplayEffectContextHandle GameplayEffectContextHandle;

	// Source Actor Info
	/** The ability system component of the source actor, used to apply and modify attributes and effects. */
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Ability System | Gameplay Effect Properties | Source")
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;

	/** The actor who applied the gameplay effect (e.g., the character or pawn that triggered the effect). */
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Ability System | Gameplay Effect Properties | Source")
	TObjectPtr<AActor> SourceAvatarActor;

	/** The controller of the source actor, which could be a player or AI controller. */
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Ability System | Gameplay Effect Properties | Source")
	TObjectPtr<AController> SourceController;

	/** The character associated with the source actor. Used to link gameplay effects to character-specific behavior. */
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Ability System | Gameplay Effect Properties | Source")
	TObjectPtr<ACharacter> SourceCharacter;

	// Target Actor Info
	/** The ability system component of the target actor, used to modify target attributes and apply effects. */
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Ability System | Gameplay Effect Properties | Target")
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;

	/** The actor receiving the gameplay effect. This could be an enemy, NPC, or another player. */
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Ability System | Gameplay Effect Properties | Target")
	TObjectPtr<AActor> TargetAvatarActor;

	/** The controller associated with the target actor. Used for managing the target's actions. */
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Ability System | Gameplay Effect Properties | Target")
	TObjectPtr<AController> TargetController;

	/** The character associated with the target actor, useful for applying gameplay effects to character behavior. */
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Ability System | Gameplay Effect Properties | Target")
	TObjectPtr<ACharacter> TargetCharacter;

	// Constructor to initialize all pointers to null.
	FGameplayEffectProperties()
		: SourceAbilitySystemComponent(nullptr)
		, SourceAvatarActor(nullptr)
		, SourceController(nullptr)
		, SourceCharacter(nullptr)
		, TargetAbilitySystemComponent(nullptr)
		, TargetAvatarActor(nullptr)
		, TargetController(nullptr)
		, TargetCharacter(nullptr)
	{}
};

UCLASS()
class GASPLUGIN_API UGASPAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	UGASPAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


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

	/** 
	 * These functions are executed when the attribute is replicated.
	 * They are useful for triggering visual effects, like updating UI elements when an attribute value changes.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthChanged, Category = "GASP Plugin | Vital Attributes", Meta=(DisplayName="VitalAttributes.Health"))
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGASPAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealthChanged, Category = "GASP Plugin | Vital Attributes", Meta=(DisplayName="VitalAttributes.MaxHealth"))
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

protected:

	/** Function to fill in the effect properties after a gameplay effect executes */
	virtual void SetGameplayEffectProperties(const struct FGameplayEffectModCallbackData& Data, FGameplayEffectProperties& EffectProperties) const;
};

