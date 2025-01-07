// Copyright Heathrow


#include "Player/GASPPlayerState.h"

#include "AbilitySystem/GASPAbilitySystemComponent.h"
#include "AbilitySystem/GASPAttributeSet.h"

AGASPPlayerState::AGASPPlayerState()
{
	SetNetUpdateFrequency(100.f);

	// Initialize Ability System Component and Attribute Set
	AbilitySystemComponent = CreateDefaultSubobject<UGASPAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(GameplayEffectReplicationMode);

	AttributeSet = CreateDefaultSubobject<UGASPAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGASPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AGASPPlayerState::GetAttributeSetComponent() const
{
	return AttributeSet;
}
