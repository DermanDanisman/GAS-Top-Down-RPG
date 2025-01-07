// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "Character/TDCharacterBase.h"
#include "TDPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_TOPDOWNRPG_API ATDPlayerCharacter : public ATDCharacterBase
{
	GENERATED_BODY()

public:
	
	ATDPlayerCharacter();

protected:

	virtual void BeginPlay() override;
	
};
