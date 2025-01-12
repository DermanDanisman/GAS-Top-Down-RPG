// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GASPHUD.generated.h"



/** Forward Declaration */
class UGASPUserWidget;
class UGASPWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FGASPWidgetControllerData;

/**
 * This class represents the HUD (Head-Up Display) for the GAS (Gameplay Ability System) Plugin.
 * It manages the Main Overlay Widget, its controller, and the logic for initializing and displaying UI elements.
 */
UCLASS()
class GASPLUGIN_API AGASPHUD : public AHUD
{
	GENERATED_BODY()

public:
	/**
	 * Reference to the Main Overlay Widget, which is the primary widget in the HUD.
	 * This widget is responsible for displaying key information to the player.
	 */
	UPROPERTY(BlueprintReadWrite, Category="GASP Plugin | HUD | Widgets | References")
	TObjectPtr<UGASPUserWidget> MainOverlayWidget;

	/**
	 * Retrieves the Main Overlay Widget Controller. If it has not been created, it instantiates it
	 * and sets it up with the provided data. This ensures only one instance of the widget controller
	 * exists within the HUD context.
	 * 
	 * @param InWidgetControllerData: Contains data needed to initialize the widget controller (e.g., PlayerController, PlayerState, etc.).
	 * 
	 * @return The Main Overlay Widget Controller instance. The caller should typically cast this controller 
	 * to a specific subclass of UGASPWidgetController depending on the widget's implementation.
	 */
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | HUD | Functions")
	UGASPWidgetController* GetMainOverlayWidgetController(const FGASPWidgetControllerData& InWidgetControllerData);

	/**
	 * This BlueprintImplementableEvent is triggered in C++ or Blueprint to initialize the Main Overlay Widget.
	 * The function should be implemented in Blueprint to handle the widget's initialization using the provided data.
	 * 
	 * @param PC: The player's controller, used to manage player inputs and interactions.
	 * @param PS: The player state, containing important player-specific data like health and score.
	 * @param ASC: The Ability System Component, which manages abilities and other related gameplay features.
	 * @param AS: The Attribute Set, which contains various player attributes like health, mana, etc.
	 * 
	 * This function allows the widget to be initialized with real-time player data and makes it ready for display.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "GASP Plugin | HUD | Functions")
	void InitializeMainOverlayWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:
	
	/**
	 * Class reference for the Main Overlay Widget (used to spawn the widget).
	 * This reference allows the widget to be set in the editor or via code.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | HUD | Widgets | Classes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGASPUserWidget> MainOverlayWidgetClass;

	/**
	 * Reference to the Main Overlay Widget Controller, which manages the logic and data flow for the widget.
	 * This reference is used to initialize, update, and control the Main Overlay Widget during runtime.
	 */
	UPROPERTY(BlueprintReadOnly, Category="GASP Plugin | HUD | Widget Controller | References", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGASPWidgetController> MainOverlayWidgetController;

	/**
	 * Class reference for the Main Overlay Widget Controller, used to spawn the controller instance.
	 * This reference can be set in the editor or via code.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | HUD | Widget Controller | Classes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGASPWidgetController> MainOverlayWidgetControllerClass;
};
