// Copyright Heathrow


#include "Character/GASPlayerCharacter.h"

#include "AbilitySystem/GAS_ManagerComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/GASPlayerState.h"

AGASPlayerCharacter::AGASPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	// Configure character movement and rotation:
	// - Align character's rotation to movement direction.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// - Set rotation speed to 500 degrees per second on the yaw axis.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	// - Constrain movement to a flat plane and snap character to plane at start.
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	// - Disable controller's influence over pitch, roll, and yaw, allowing movement-based rotation only.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AGASPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// InitAbilityActorInfo for the server
	AGASPlayerState* GASPlayerState = GetPlayerState<AGASPlayerState>();
	ensureMsgf(GASPlayerState, TEXT("GASPlayerState is null in PossessedBy!"));
	GASPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(GASPlayerState, this);

	/** GAS Plugin **/
	GASPlayerState->GASManagerComponent->InitAbilityActorInfo();;
	AbilitySystemComponent = GASPlayerState->GASManagerComponent->GetAbilitySystemComponent();
	AttributeSet = GASPlayerState->GASManagerComponent->GetAttributeSet();
}

void AGASPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void AGASPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}
