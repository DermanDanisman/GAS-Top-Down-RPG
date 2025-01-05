// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GASPPlayerController.generated.h"

/** Forward Declaration */
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
};
