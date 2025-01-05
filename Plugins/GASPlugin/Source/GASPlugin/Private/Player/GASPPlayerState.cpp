// Copyright Heathrow


#include "Player/GASPPlayerState.h"

#include "AbilitySystem/GASPAbilitySystemComponent.h"
#include "AbilitySystem/GASPAttributeSet.h"

AGASPPlayerState::AGASPPlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UGASPAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UGASPAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGASPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AGASPPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
