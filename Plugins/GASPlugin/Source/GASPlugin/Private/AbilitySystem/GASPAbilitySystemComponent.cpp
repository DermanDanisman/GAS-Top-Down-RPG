// Copyright Heathrow


#include "AbilitySystem/GASPAbilitySystemComponent.h"

UGASPAbilitySystemComponent::UGASPAbilitySystemComponent()
{
	SetIsReplicated(true);
}

void UGASPAbilitySystemComponent::AbilityActorInfoIsSet()
{
	// Binding the custom GameplayEffectApplied function to the OnGameplayEffectAppliedDelegateToSelf delegate
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UGASPAbilitySystemComponent::GameplayEffectApplied);
}

void UGASPAbilitySystemComponent::GameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer GameplayTagContainer;
	GameplayEffectSpec.GetAllAssetTags(GameplayTagContainer);

	GameplayEffectAssetTags.Broadcast(GameplayTagContainer);
}
