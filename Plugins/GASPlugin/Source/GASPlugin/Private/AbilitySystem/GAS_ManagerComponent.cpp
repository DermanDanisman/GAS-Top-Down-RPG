// Copyright Heathrow


#include "AbilitySystem/GAS_ManagerComponent.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "AbilitySystem/GAS_AbilitySystemComponent.h"
#include "AbilitySystem/GAS_AttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"

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

void UGAS_ManagerComponent::InitAbilityActorInfo()
{
	// Ensure AbilitySystemComponent exists
	if (!AbilitySystemComponent)
	{
		return;  // Early exit if no Ability System Component
	}

	// Get the PlayerState (for Player Character)
	// If it's a PlayerCharacter (PlayerState is valid)
	if (OwnerPlayerState)
	{
		// Ensure the PlayerState is valid, and initialize Ability Actor Info with PlayerState and Pawn
		ensureMsgf(OwnerPlayerState, TEXT("OwnerPlayerState is null in PossessedBy!"));
		AbilitySystemComponent->InitAbilityActorInfo(GetOwner(), GetOwner()->GetOwner());

		// Optionally, you can initialize the component here or do other setup as needed
		// Example: Initialize or add abilities
		// GiveAbility(SomeAbilityClass);
	}
	else if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		// For AI or other types of actors, check if it's an AI controller and initialize accordingly
		AController* Controller = OwnerPawn->GetController();
		if (Controller && Controller->IsA<AAIController>())
		{
			// If it's an AI controller, initialize the Ability Actor Info with Pawn as both owner and avatar
			AbilitySystemComponent->InitAbilityActorInfo(OwnerPawn, OwnerPawn);
		}
		else
		{
			// For player-controlled characters, but PlayerState is missing (handle with caution)
			UE_LOG(LogTemp, Warning, TEXT("PlayerState is missing for PlayerCharacter. This might indicate an issue with the setup."));
		}
	}

}
