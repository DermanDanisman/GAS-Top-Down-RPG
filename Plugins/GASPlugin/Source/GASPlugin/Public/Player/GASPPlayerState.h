// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GASPPlayerState.generated.h"

/** Forward Declaration */
enum class EGameplayEffectReplicationMode : uint8;

/**
 * 
 */
UCLASS()
class GASPLUGIN_API AGASPPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AGASPPlayerState();

	/** Ability System Interface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSetComponent() const;
	
protected:

	/** Ability System */
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditAnywhere, Category = "GASP Plugin | Ability System")
	EGameplayEffectReplicationMode GameplayEffectReplicationMode = EGameplayEffectReplicationMode::Mixed;
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;
};
