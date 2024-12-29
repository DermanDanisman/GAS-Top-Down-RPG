// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GASPlayerController.generated.h"

/** Forward Declaration */
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class GAS_TOPDOWNRPG_API AGASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AGASPlayerController();

protected:

	virtual void BeginPlay() override;
	void SetupInputComponent() override;

private:

	UPROPERTY(EditAnywhere, Category="Enhanced Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
};
