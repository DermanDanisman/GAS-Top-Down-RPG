// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacterBase.h"
#include "GASPlayerCharacter.generated.h"

/** Forward Declaration */
class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class GAS_TOPDOWNRPG_API AGASPlayerCharacter : public AGASCharacterBase
{
	GENERATED_BODY()

public:
	AGASPlayerCharacter();
	void InitAbilityActorInfo();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void BeginPlay() override;

private:

	/** Camera Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
};
