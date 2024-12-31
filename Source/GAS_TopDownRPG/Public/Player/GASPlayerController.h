// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GASPlayerController.generated.h"

/** Forward Declaration */
class UInputMappingContext;
class UInputAction;
class IHighlightableInterface;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class GAS_TOPDOWNRPG_API AGASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AGASPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
	void SetupInputComponent() override;

private:

	TScriptInterface<IHighlightableInterface> HighlightedLastActor;
	TScriptInterface<IHighlightableInterface> HighlightedCurrentActor;
	void CursorTrace();


	/** Enhanced Input Functions */
	void Move(const FInputActionValue& InputActionValue);
	
	/** Enhanced Input Variables */
	UPROPERTY(EditAnywhere, Category="Enhanced Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere, Category="Enhanced Input")
	TObjectPtr<UInputAction> MoveAction;
	

};
