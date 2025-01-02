// Copyright Heathrow


#include "Player/GASPlayerState.h"

#include "AbilitySystem/GASAbilitySystemComponent.h"
#include "AbilitySystem/GASAttributeSet.h"

AGASPlayerState::AGASPlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGASPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AGASPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
