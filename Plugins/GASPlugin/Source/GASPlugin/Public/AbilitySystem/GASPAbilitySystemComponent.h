// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GASPAbilitySystemComponent.generated.h"

// Delegate that will be used to broadcast gameplay effect asset tags when an effect is applied.
DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayEffectTags, const FGameplayTagContainer& /*AssetTags*/)

/**
 * Custom Ability System Component class derived from UAbilitySystemComponent.
 * This class extends the default ability system component to provide additional functionality
 * for tracking gameplay effect tags when an effect is applied.
 */
UCLASS()
class GASPLUGIN_API UGASPAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UGASPAbilitySystemComponent();

	/**
	 * Function to bind the callback function to the GameplayEffectApplied event.
	 * This should be called when the actor info is set, ensuring that effects are properly tracked.
	 */
	void AbilityActorInfoIsSet();

	// Delegate instance that will broadcast gameplay effect asset tags when an effect is applied.
	FGameplayEffectTags GameplayEffectAssetTags;

protected:

	/**
	 * Function that gets called when a gameplay effect is applied to this component.
	 * This function extracts gameplay tags from the effect and broadcasts them.
	 */
	virtual void GameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
