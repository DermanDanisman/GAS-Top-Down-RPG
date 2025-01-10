// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GASPWidgetController.generated.h"
 
/** Forward Declaration */
class UAttributeSet;
class UAbilitySystemComponent;

/**
 * This class exists in a domain that we'll call the controller (Widget Controller) in MVC system,
 * and the controller will be responsible for retrieving data from the model (Data from Player Controller, Player State etc.)
 * and passing it to the view (UI / Widgets) so it can depict data visually.
 * Dependencies: View (UI / Widgets) -> Controller (Widget Controller) -> Model (Data from Player Controller, Player State etc.)
 */
UCLASS()
class GASPLUGIN_API UGASPWidgetController : public UObject
{
	GENERATED_BODY()

protected:

	// References to key objects in the GAS system
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | References")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | References")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | References")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | References")
	TObjectPtr<UAttributeSet> AttributeSet;
};
