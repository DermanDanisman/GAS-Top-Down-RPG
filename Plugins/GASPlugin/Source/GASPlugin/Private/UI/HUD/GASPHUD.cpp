// Copyright Heathrow


#include "UI/HUD/GASPHUD.h"

#include "UI/Widget/GASPUserWidget.h"

void AGASPHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>((GetWorld()), MainOverlayWidgetClass);
	Widget->AddToViewport();
}
