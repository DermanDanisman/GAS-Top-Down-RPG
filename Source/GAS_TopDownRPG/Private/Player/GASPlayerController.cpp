// Copyright Heathrow


#include "Player/GASPlayerController.h"

#include "EnhancedInputSubsystems.h"

AGASPlayerController::AGASPlayerController()
{
	bReplicates = true;
}

void AGASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Ensure PlayerMappingContext is set
	ensureMsgf(DefaultMappingContext, TEXT("PlayerMappingContext must be set in GASPlayerController!"));

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	// Ensure EnhancedInputSubsystem is valid
	ensureMsgf(EnhancedInputSubsystem, TEXT("EnhancedInputSubsystem is null!"));
	EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext, 0);

	// Set Mouse Settings
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
