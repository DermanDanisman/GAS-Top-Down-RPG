// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HighlightableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHighlightableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 	Created pure virtual functions in this class which means that we will not provide a definition for them.
 * 	This class is now considered abstract and must be derived from. Any class that implements this interface must implement its functions
 */
class GAS_TOPDOWNRPG_API IHighlightableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};
