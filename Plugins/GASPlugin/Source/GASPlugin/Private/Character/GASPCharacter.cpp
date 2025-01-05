// Copyright Heathrow


#include "Character/GASPCharacter.h"

#include "AbilitySystem/GASPAbilitySystemComponent.h"
#include "AbilitySystem/GASPAttributeSet.h"
#include "Player/GASPPlayerController.h"
#include "Player/GASPPlayerState.h"

// Sets default values
AGASPCharacter::AGASPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGASPCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!GetController()->GetClass()->IsChildOf(AGASPPlayerController::StaticClass()))
	{
		AbilitySystemComponent = CreateDefaultSubobject<UGASPAbilitySystemComponent>("AbilitySystemComponent");
		AbilitySystemComponent->SetIsReplicated(true);
		AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

		AttributeSet = CreateDefaultSubobject<UGASPAttributeSet>("AttributeSet");
		
		// Initialize the Ability Actor Info
		ensureMsgf(AbilitySystemComponent, TEXT("AbilitySystemComponent is null in GAS Enemy Character!"));
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AGASPCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (GetController()->GetClass()->IsChildOf(AGASPPlayerController::StaticClass()))
	{
		InitAbilityActorInfo();
	}
}

void AGASPCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (GetController()->GetClass()->IsChildOf(AGASPPlayerState::StaticClass()))
	{
		InitAbilityActorInfo();
	}
}

UAbilitySystemComponent* AGASPCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AGASPCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void AGASPCharacter::InitAbilityActorInfo()
{
	AGASPPlayerState* GASPPlayerState = GetPlayerState<AGASPPlayerState>();
	ensureMsgf(GASPPlayerState, TEXT("GASPlayerState is null in PossessedBy!"));
	GASPPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(GASPPlayerState, this);
	AbilitySystemComponent = GASPPlayerState->GetAbilitySystemComponent();
	AttributeSet = GASPPlayerState->GetAttributeSet();
}

