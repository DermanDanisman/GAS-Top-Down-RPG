// Copyright Heathrow


#include "Character/TDEnemyCharacter.h"

#include "GAS_TopDownRPG/GAS_TopDownRPG.h"


ATDEnemyCharacter::ATDEnemyCharacter()
{
	// This is needed for the Custom Depth to work correctly. By setting it to block, you ensure that the mesh interacts with the custom depth rendering pipeline.
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	InitializeAbilitySystem();
}

void ATDEnemyCharacter::HighlightActor()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_STENCIL_RED);
	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_STENCIL_RED);
}

void ATDEnemyCharacter::UnHighlightActor()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}
