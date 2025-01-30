// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GASPWidgetController.generated.h"

/** Forward Declaration */
class UAttributeSet;
class UAbilitySystemComponent;


USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	FGameplayTag GameplayTag;
};

/**
 * Struct for holding the data required for the Widget Controller, 
 * which includes references to player-related objects (PlayerController, PlayerState),
 * AbilitySystemComponent (for interacting with the player's abilities), and the AttributeSet (player stats).
 */
USTRUCT(BlueprintType)
struct FGASPWidgetControllerData
{
	GENERATED_BODY()

	FGASPWidgetControllerData() {}
	FGASPWidgetControllerData(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	// Member initializer list
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	// References to player-related objects and components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASP Plugin | Widget Controller | Core Data")
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASP Plugin | Widget Controller | Core Data")
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASP Plugin | Widget Controller | Core Data")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASP Plugin | Widget Controller | Core Data")
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * This class exists in a domain that we'll call the controller (Widget Controller) in MVC system,
 * and the controller will be responsible for retrieving data from the model (Data from Player Controller, Player State etc.)
 * and passing it to the view (UI / Widgets) so it can depict data visually.
 * Dependencies: View (UI / Widgets) -> Controller (Widget Controller) -> Model (Data from Player Controller, Player State etc.)
 */
UCLASS()
class GASPLUGIN_API UGASPWidgetController : public UObject
{
	GENERATED_BODY()

public:
	
	/**
	 Sets the data for the Widget Controller from the provided structure (FGASPWidgetControllerData).
	 This function updates the internal references for the PlayerController, PlayerState,
	 AbilitySystemComponent, and AttributeSet from the provided input data.
	 It is used to initialize or update the widget controller with the necessary game data
	 so that the widget controller can access and interact with the player's ability system and attributes.
	 */
	void SetWidgetControllerData(const FGASPWidgetControllerData& InWidgetControllerData);

	// This method can be used to broadcast the initial values of the widget
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Widget Controller")
	virtual void BroadcastInitialValues();

	// This method registers callbacks for attribute change notifications.
	// It will likely respond to any changes in player's attributes like health, mana, etc.
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Widget Controller")
	virtual void RegisterAttributeChangeCallbacks();

protected:

	// References to key objects in the GAS system
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | Core References")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | Core References")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | Core References")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | Core References")
	TObjectPtr<UAttributeSet> AttributeSet;
};
