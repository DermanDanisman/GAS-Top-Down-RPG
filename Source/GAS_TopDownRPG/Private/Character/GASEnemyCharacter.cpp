// Copyright Heathrow


#include "Character/GASEnemyCharacter.h"

#include "GAS_TopDownRPG/GAS_TopDownRPG.h"

AGASEnemyCharacter::AGASEnemyCharacter()
{
	// This is needed for the Custom Depth to work correctly. By setting it to block, you ensure that the mesh interacts with the custom depth rendering pipeline.
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
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
