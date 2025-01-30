// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GASPAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASPLUGIN_API UGASPAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UGASPAbilitySystemComponent();

	/**
	 * Function to bind the callback function to the GameplayEffectApplied event
	 */
	void AbilityActorInfoIsSet();

protected:

	/**
	 * Binding this to OnGameplayEffectAppliedDelegateToSelf, which means we have GameplayEffectApplied a callback function
	 * that will be called in response to any effect that gets applied to this ability system component.
	 */
	virtual void GameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
