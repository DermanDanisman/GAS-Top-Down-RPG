// Copyright Heathrow


#include "Character/TDPlayerCharacter.h"

ATDPlayerCharacter::ATDPlayerCharacter()
{
}

void ATDPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ApplyMovementConfig();
}
