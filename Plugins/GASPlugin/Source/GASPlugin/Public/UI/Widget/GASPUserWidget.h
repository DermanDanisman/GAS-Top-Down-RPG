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

	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | GASP User Widget")
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | GASP User Widget | References")
	TObjectPtr<UObject> WidgetController;

protected:

	// Will be called when the widget controller is set.
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | GASP User Widget")
	void WidgetControllerIsSet();
};
