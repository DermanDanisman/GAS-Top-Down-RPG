// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GASPWidgetController.generated.h"
 
/** Forward Declaration */
class UAttributeSet;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class GASPLUGIN_API UGASPWidgetController : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | References")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | References")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | References")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | References")
	TObjectPtr<UAttributeSet> AttributeSet;
};
