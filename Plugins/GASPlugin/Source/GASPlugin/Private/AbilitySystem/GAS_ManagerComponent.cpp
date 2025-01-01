// Copyright Heathrow


#include "AbilitySystem/GAS_ManagerComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GAS_AbilitySystemComponent.h"
#include "AbilitySystem/GAS_AttributeSet.h"

// Sets default values for this component's properties
UGAS_ManagerComponent::UGAS_ManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);

	AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ReplicationMode);

	AttributeSet = CreateDefaultSubobject<UGAS_AttributeSet>("AttributeSet");
}

// Called when the game starts
void UGAS_ManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}

UAbilitySystemComponent* UGAS_ManagerComponent::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* UGAS_ManagerComponent::GetAttributeSet() const
{
	return AttributeSet;
}
