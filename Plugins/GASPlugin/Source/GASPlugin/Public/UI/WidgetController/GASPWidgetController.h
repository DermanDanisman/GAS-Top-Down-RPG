// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GASPWidgetController.generated.h"


/** Forward Declaration */
class UAttributeSet;
class UAbilitySystemComponent;
class UGASPUserWidget;

/**
 * Struct for defining a single row of UI widget data.
 * Includes details like the message text, an associated gameplay tag, widget class, and an image for the widget.
 */
USTRUCT(BlueprintType)
struct FUIMessageWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	FUIMessageWidgetRow() {}

	// Gameplay tag for the message in this row, used for categorization or specific conditions (e.g., health, mana, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | UI Widget Row")
	FGameplayTag MessageGameplayTag;

	// The text of the message displayed in the widget (e.g., "Health Low")
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | UI Widget Row")
	FText MessageText = FText();

	// The widget class to be displayed (which widget will be used to display the message)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | UI Widget Row")
	TSubclassOf<UGASPUserWidget> MessageWidgetClass;

	// An optional image to accompany the message, such as an icon for the message type
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | UI Widget Row")
	UTexture2D* Image = nullptr;
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

	// Data table that holds UI widget data (e.g., text, image, widget class)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	// References to key objects in the GAS system
	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | Core References")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | Core References")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | Core References")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "GASP Plugin | Widget Controller | Core References")
	TObjectPtr<UAttributeSet> AttributeSet;

protected:

	/**
	 * Template functions are a feature in C++ that allow functions to operate with generic types.
	 * This is achieved through the use of templates, which provide a way to write a single function
	 * (or class) to work with different data types without rewriting the entire function (or class) for each type.
	 *
	 * What is a Template Function?
	 * A template function is a function that can operate on data of any type.
	 * The type is specified when the function is called.
	 * The syntax involves the template keyword followed by template parameters enclosed in angle brackets <>.
	 * 
	 * Why Use Template Functions?
	 * Reusability: Write a function once and use it with different data types.
	 * Type Safety: Provides compile-time type checking, ensuring that only valid types are used.
	 * Maintainability: Easier to maintain since the logic for different data types is encapsulated in a single function definition.
	 *
	 * When to Use Template Functions
	 * Generic Operations: When you need a function to perform operations that are independent of the data type.
	 * Data Structures: Implementing data structures like linked lists, stacks, queues, trees, etc., that should work with any data type.
	 * Code Reusability: When you find yourself writing the same function logic for multiple data types, it's a good candidate for templating.
	 *
	 * GetDataTableRowByTag function finds a row in the data table that matches the given gameplay tag name, and returns a pointer to that row cast to type T.
	 */
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& GameplayTag);
};

template <typename T>
T* UGASPWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& GameplayTag)
{
	return DataTable->FindRow<T>(GameplayTag.GetTagName(), TEXT(""));
}
