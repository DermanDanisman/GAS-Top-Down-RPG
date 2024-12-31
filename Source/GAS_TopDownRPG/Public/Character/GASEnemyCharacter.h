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
	
	/** Highlightable Interface */
	virtual void Highlight(bool bIsHighlighted) override;
	virtual void UnHighlight(bool bIsHighlighted) override;
};
