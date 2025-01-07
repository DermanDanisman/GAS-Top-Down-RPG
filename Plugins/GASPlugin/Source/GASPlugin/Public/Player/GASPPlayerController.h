// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GASPPlayerController.generated.h"

/** Forward Declaring */
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class GASPLUGIN_API AGASPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGASPPlayerController();

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category="GASP Plugin | Enhanced Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	void Move(const FInputActionValue& InputActionValue);
	UPROPERTY(EditAnywhere, Category="GASP Plugin | Enhanced Input")
	TObjectPtr<UInputAction> MoveInputAction;
};
