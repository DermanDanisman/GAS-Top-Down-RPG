// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "Character/GASPCharacter.h"
#include "Interface/HighlightableInterface.h"
#include "TDCharacterBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GAS_TOPDOWNRPG_API ATDCharacterBase : public AGASPCharacter
{
	GENERATED_BODY()

public:
	ATDCharacterBase();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
};
