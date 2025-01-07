// Copyright Heathrow


#include "Character/GASPCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GASPAbilitySystemComponent.h"
#include "AbilitySystem/GASPAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	InitAbilityActorInfo();
}

void AGASPCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void AGASPCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

void AGASPCharacter::InitAbilityActorInfo()
{
	if (!IsPlayerControlled())
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	else
	{
		AGASPPlayerState* GASPPlayerState = GetPlayerState<AGASPPlayerState>();
		ensureMsgf(GASPPlayerState, TEXT("GASPPlayerState Is Not Valid!"));
		if (GASPPlayerState)
		{
			GASPPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(GASPPlayerState, this);
			AbilitySystemComponent = GASPPlayerState->GetAbilitySystemComponent();
			AttributeSet = GASPPlayerState->GetAttributeSetComponent();
		}
	}
}

UAbilitySystemComponent* AGASPCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AGASPCharacter::GetAttributeSetComponent() const
{
	return AttributeSet;
}

void AGASPCharacter::ApplyMovementConfig()
{
    GetCharacterMovement()->bOrientRotationToMovement = MovementConfig.bOrientRotationToMovement;
    GetCharacterMovement()->RotationRate = MovementConfig.RotationRate;
    GetCharacterMovement()->bConstrainToPlane = MovementConfig.bConstrainToPlane;
    GetCharacterMovement()->bSnapToPlaneAtStart = MovementConfig.bSnapToPlaneAtStart;
    bUseControllerRotationPitch = MovementConfig.bUseControllerRotationPitch;
    bUseControllerRotationYaw = MovementConfig.bUseControllerRotationYaw;
    bUseControllerRotationRoll = MovementConfig.bUseControllerRotationRoll;
}

void AGASPCharacter::InitializeAbilitySystem()
{
	// Initialize Ability System Component and Attribute Set
	AbilitySystemComponent = CreateDefaultSubobject<UGASPAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(GameplayEffectReplicationMode);

	AttributeSet = CreateDefaultSubobject<UGASPAttributeSet>("AttributeSet");
}

