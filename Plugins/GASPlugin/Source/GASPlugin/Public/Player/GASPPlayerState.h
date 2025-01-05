// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GASPPlayerState.generated.h"

/** Forward Declaration */
class UGASPAttributeSet;
class UGASPAbilitySystemComponent;
class UAttributeSet;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class GASPLUGIN_API AGASPPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASPPlayerState();

	/** IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;

protected:

	UPROPERTY(EditAnywhere, Category = "GASP Plugin | Ability System")
	EGameplayEffectReplicationMode GameplayEffectReplicationMode = EGameplayEffectReplicationMode::Mixed;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
};
