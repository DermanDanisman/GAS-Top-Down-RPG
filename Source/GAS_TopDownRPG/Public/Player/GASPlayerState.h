// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GASPlayerState.generated.h"

/** Forward Declaration */
class UAttributeSet;
class UAbilitySystemComponent;
class UGAS_ManagerComponent;

/**
 * 
 */
UCLASS()
class GAS_TOPDOWNRPG_API AGASPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASPlayerState();

	/** IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;

protected:

	//** GAS Plugin **//
	UPROPERTY(VisibleAnywhere, Category="GAS Plugin")
	TObjectPtr<UGAS_ManagerComponent> GASManagerComponent;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
