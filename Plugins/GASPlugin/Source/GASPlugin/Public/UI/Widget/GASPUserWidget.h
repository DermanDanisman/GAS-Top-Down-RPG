// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GASPUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GASPLUGIN_API UGASPUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// Function to set the Widget Controller
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | GASP User Widget")
	void SetWidgetController(UObject* InWidgetController);

	// A reference to the Widget Controller
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | GASP User Widget | References")
	TObjectPtr<UObject> WidgetController;

protected:

	// Will be called when the Widget Controller is set
	UFUNCTION(BlueprintImplementableEvent, Category = "GASP Plugin | GASP User Widget")
	void WidgetControllerIsSet();
};
