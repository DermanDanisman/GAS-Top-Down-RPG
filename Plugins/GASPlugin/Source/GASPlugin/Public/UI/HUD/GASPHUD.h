// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GASPHUD.generated.h"

/** Forward Declaration */
class UGASPUserWidget;
/**
 * 
 */
UCLASS()
class GASPLUGIN_API AGASPHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UGASPUserWidget> MainOverlayWidget;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "GASP Plugin | HUD")
	TSubclassOf<UGASPUserWidget> MainOverlayWidgetClass;
};
