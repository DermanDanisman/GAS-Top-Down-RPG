// Copyright Heathrow


#include "UI/WidgetController/GASPWidgetController.h"

#include "AbilitySystem/GASPAbilitySystemComponent.h"

void UGASPWidgetController::SetWidgetControllerData(const FGASPWidgetControllerData& InWidgetControllerData)
{
	PlayerController = InWidgetControllerData.PlayerController;
	PlayerState = InWidgetControllerData.PlayerState;
	AbilitySystemComponent = InWidgetControllerData.AbilitySystemComponent;
	AttributeSet = InWidgetControllerData.AttributeSet;
}

void UGASPWidgetController::BroadcastInitialValues()
{
	
}

void UGASPWidgetController::RegisterAttributeChangeCallbacks()
{
	/*
	 * What is AddLambda?
	 * AddLambda is a method used to bind a lambda function to a delegate in Unreal Engine.
	 * A lambda function is an anonymous function that can capture variables from its surrounding scope.
	 * It's a convenient way to define small, inline functions without having to write a separate function.
	 *
	 * How Does AddLambda Work?
	 * When you call AddLambda on a delegate, you pass in a lambda function that you want to bind to that delegate.
	 * The delegate then stores the lambda and calls it whenever the delegate is broadcasted.
	 *
	 * Why Use AddLambda?
 	 * Inline Functions: AddLambda allows you to define small functions inline where they are used, which can make your code more readable and localized.
	 * Capture Local Variables: You can capture local variables within the lambda, making it easier to access local state without passing additional parameters.
	 * Flexibility: It provides a flexible way to quickly bind behavior to delegates without needing to define separate callback functions.
	 * Reduced Boilerplate: Reduces the need to define multiple small callback functions and their associated boilerplate code.
	 *
	 * Why Use a Lambda Here?
	 * Localization: The lambda function is defined right where it's used, making it easy to see the relationship between the delegate and its handler.
	 * Simplicity: No need to define a separate member function if the logic is simple and used only in this context.
	 * Access to Local Variables: Although this example doesn't capture any local variables, lambdas can capture local state if needed, which can be very convenient.
	 *
	 * The square brackets are for captures. If we want to access a member variable from something, then that thing, that class that has the member variable must be captured within the lambda.
	 * Now we can capture variables, we can capture things by reference, we can capture things by pointer.
	 * So if you want to call a member function in a lambda, you have to capture that object of the class that that function belongs to.
	 */
	Cast<UGASPAbilitySystemComponent>(AbilitySystemComponent)->GameplayEffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
	{
		// Process each gameplay tag here and broadcast it to the widget
		// This would be useful for updating the UI based on certain tags from gameplay effects
		for (const FGameplayTag& GameplayTag : AssetTags)
		{
			//TODO: Broadcast the tag to the widget controller.
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, FString::Printf(TEXT("Effect Applied Tag: %s"), *GameplayTag.GetTagName().ToString()));
			FUIMessageWidgetRow* Row = GetDataTableRowByTag<FUIMessageWidgetRow>(MessageWidgetDataTable, GameplayTag);
		}
	}
);
}
