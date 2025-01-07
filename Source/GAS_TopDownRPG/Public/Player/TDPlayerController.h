// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "Player/GASPPlayerController.h"
#include "TDPlayerController.generated.h"

/** Forward Declaration */
class IHighlightableInterface;
/**
 * 
 */
UCLASS()
class GAS_TOPDOWNRPG_API ATDPlayerController : public AGASPPlayerController
{
	GENERATED_BODY()

public:

	virtual void PlayerTick(float DeltaTime) override;
	
protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	void SetUpMouseCursorAndInputMode();

	/** Cursor */
	TScriptInterface<IHighlightableInterface> HighlightedLastActor;
	TScriptInterface<IHighlightableInterface> HighlightedCurrentActor;
	void CursorTrace();
};
