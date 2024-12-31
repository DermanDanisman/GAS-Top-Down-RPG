// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacterBase.h"
#include "Interface/HighlightableInterface.h"
#include "GASEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_TOPDOWNRPG_API AGASEnemyCharacter : public AGASCharacterBase, public IHighlightableInterface
{
	GENERATED_BODY()

public:
	AGASEnemyCharacter();
	
	/** Highlightable Interface */
	virtual void Highlight() override;
	virtual void UnHighlight() override;
	bool bHighlighted = false;
};
