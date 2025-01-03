// Copyright Heathrow


#include "Character/GASEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GASAbilitySystemComponent.h"
#include "AbilitySystem/GASAttributeSet.h"
#include "GAS_TopDownRPG/GAS_TopDownRPG.h"

AGASEnemyCharacter::AGASEnemyCharacter()
{
	// This is needed for the Custom Depth to work correctly. By setting it to block, you ensure that the mesh interacts with the custom depth rendering pipeline.
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSet>("AttributeSet");
	
}

void AGASEnemyCharacter::Highlight()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_STENCIL_RED);
	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_STENCIL_RED);
}

void AGASEnemyCharacter::UnHighlight()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}

void AGASEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the Ability Actor Info
	ensureMsgf(AbilitySystemComponent, TEXT("AbilitySystemComponent is null in GAS Enemy Character!"));
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
