// Copyright Heathrow


#include "Character/GASPCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GASPAbilitySystemComponent.h"
#include "AbilitySystem/GASPAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/GASPPlayerController.h"
#include "Player/GASPPlayerState.h"
#include "UI/HUD/GASPHUD.h"


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
	// Check if the character is player-controlled
	if (!IsPlayerControlled())
	{
		// For non-player-controlled characters, initialize the ability actor info using the current character and itself as owner
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	else
	{
		// If the character is player-controlled, initialize using the player state
		AGASPPlayerState* GASPPlayerState = GetPlayerState<AGASPPlayerState>();

		// Ensure the player state is valid before proceeding
		ensureMsgf(GASPPlayerState, TEXT("GASPPlayerState Is Not Valid!"));

		// If the player state is valid, initialize the ability system and set up related components
		if (GASPPlayerState)
		{
			// Initialize ability actor info using the player state and the current character
			GASPPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(GASPPlayerState, this);

			// Set the ability system component and attribute set from the player state
			AbilitySystemComponent = GASPPlayerState->GetAbilitySystemComponent();
			AttributeSet = GASPPlayerState->GetAttributeSetComponent();

			// Initializing a main overlay widget
			InitializeMainOverlayWidget(GASPPlayerState);
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
	// Create and initialize the Ability System Component for this character
	AbilitySystemComponent = CreateDefaultSubobject<UGASPAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true); // Ensure replication for multiplayer support
	AbilitySystemComponent->SetReplicationMode(GameplayEffectReplicationMode); // Set replication mode for gameplay effects

	// Create and initialize the Attribute Set for this character
	AttributeSet = CreateDefaultSubobject<UGASPAttributeSet>("AttributeSet");
}

void AGASPCharacter::InitializeMainOverlayWidget(AGASPPlayerState* GASPPlayerState)
{
	// Get the player controller associated with this character.
	AGASPPlayerController* GASPPlayerController = Cast<AGASPPlayerController>(GetController());

	// We perform a null check here because, in multiplayer scenarios, the player controller may not always be valid.
	// The player controller is guaranteed to be valid only for the locally controlled character on the client machine.
	// In a multiplayer setup, the player controller is valid only for the player controlling that specific character.
	// Other player characters, controlled by different players or the server, will not have valid player controllers
	// on this client's machine. Hence, we cannot assume that the player controller will always be valid.

	// If the player controller is valid (non-null), continue to initialize the Main Overlay Widget for this character.
	if (GASPPlayerController)
	{
		// Get the HUD associated with the player controller.
		// Again, we check if the HUD is valid, as the HUD may not be initialized or available in certain conditions.
		AGASPHUD* GASPHUD = Cast<AGASPHUD>(GASPPlayerController->GetHUD());

		// If the HUD is valid, proceed to initialize the Main Overlay Widget using the provided data.
		if (GASPHUD)
		{
			// Call the InitializeMainOverlayWidget function to set up the main overlay widget for this player.
			// This function will only be called if both the player controller and the HUD are valid,
			// ensuring that we are working with valid objects.
			GASPHUD->InitializeMainOverlayWidget(GASPPlayerController, GASPPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

