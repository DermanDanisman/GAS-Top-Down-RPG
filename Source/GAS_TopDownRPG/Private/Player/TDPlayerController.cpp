// Copyright Heathrow


#include "Player/TDPlayerController.h"

#include "Interface/HighlightableInterface.h"

void ATDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetUpMouseCursorAndInputMode();
}

void ATDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ATDPlayerController::SetUpMouseCursorAndInputMode()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ATDPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	HighlightedLastActor = HighlightedCurrentActor;
	HighlightedCurrentActor = CursorHit.GetActor();

	if (HighlightedLastActor != HighlightedCurrentActor)
	{
		if (HighlightedLastActor)
		{
			HighlightedLastActor->UnHighlightActor();
		}
		if (HighlightedCurrentActor)
		{
			HighlightedCurrentActor->HighlightActor();
		}
	}
}
