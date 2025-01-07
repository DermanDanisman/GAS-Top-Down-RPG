// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "Character/TDCharacterBase.h"
#include "TDEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_TOPDOWNRPG_API ATDEnemyCharacter : public ATDCharacterBase, public IHighlightableInterface
{
	GENERATED_BODY()

public:

	ATDEnemyCharacter();
	
	/** Highlightable Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	bool bHighlighted = false;
	/** end Highlightable Interface */
};
