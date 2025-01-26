// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "GASPEffectActor.generated.h"

/** Forward Declaration */
class UGameplayEffect;
class UGASPAbilitySystemComponent;

/**
 * Enum for managing the application policies for the gameplay effects.
 * Determines when and how the effects will be applied to a target.
 */
UENUM(BlueprintType)
enum class EGameplayEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,   // Apply the effect when overlap starts
	ApplyOnEndOverlap, // Apply the effect when overlap ends
	DoNotApply, // Do not apply the effect
};

/**
 * Enum for managing the removal policies for the gameplay effects.
 * Determines when and how the effects should be removed from a target.
 */
UENUM(BlueprintType)
enum class EGameplayEEffectRemovalPolicy : uint8
{
	RemoveOnOverlap,  // Remove the effect when overlap starts
	RemoveOnEndOverlap, // Remove the effect when overlap ends
	DoNotRemove, // Do not remove the effect
};

/**
 * Struct that holds data for each type of gameplay effect to apply.
 * It includes the gameplay effect class and its associated application policy.
 */
USTRUCT(BlueprintType)
struct FGameplayEffectInfo
{
	GENERATED_BODY()

	FGameplayEffectInfo()
		: ApplicationPolicy(EGameplayEffectApplicationPolicy::DoNotApply), RemovalPolicy(EGameplayEEffectRemovalPolicy::DoNotRemove),
		  StackRemovalCount(-1), bDestroyActorOnEffectApplication(false), bDestroyActorOnEffectRemoval(false)
	{
	}

	FGameplayEffectInfo(const TSubclassOf<UGameplayEffect>& InEffectClass, const EGameplayEffectApplicationPolicy InApplicationPolicy, const EGameplayEEffectRemovalPolicy InRemovalPolicy)
		: GameplayEffectClass(InEffectClass), ApplicationPolicy(InApplicationPolicy), RemovalPolicy(InRemovalPolicy),
		  StackRemovalCount(-1), bDestroyActorOnEffectApplication(false), bDestroyActorOnEffectRemoval(false)

	{
	}

	/** 
	 * TSubclassOf<UGameplayEffect> allows us to reference a subclass of UGameplayEffect.
	 * This property lets us define the Gameplay Effect that will be applied to targets.
	 * Set in the editor to specify which effect the actor will apply.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Applied Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	// The policy for how and when the effect is applied
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Applied Effects")
	EGameplayEffectApplicationPolicy ApplicationPolicy;

	// The policy for how and when the effect is removed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Applied Effects")
	EGameplayEEffectRemovalPolicy RemovalPolicy;

	// How many "stacks" of the effect to remove. -1 means remove all stacks
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Gameplay Effects Properties")
	int StackRemovalCount;

	// Flag to determine whether to destroy the actor after applying the effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Applied Effects | Flags")
	bool bDestroyActorOnEffectApplication;
	
	// Flag to determine whether to destroy the actor after removing the effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Applied Effects | Flags")
	bool bDestroyActorOnEffectRemoval;
};

/**
 * AGASPEffectActor is an actor class designed to apply Gameplay Effects to other actors within the game.
 * It is intended to be used with Unreal Engine's Gameplay Ability System (GAS) to apply abilities or effects to a target.
 */
UCLASS()
class GASPLUGIN_API AGASPEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGASPEffectActor();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** 
	 * Array of gameplay effect data including effect class and policies (application and removal).
	 * It consolidates all gameplay effects into one list for management.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Applied Effects")
	TArray<FGameplayEffectInfo> GameplayEffects;

	/**
	 * Map of active gameplay effect handles, used to track which effects are applied to which ability system components.
	 */
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Applied Effects")
	TMap<FActiveGameplayEffectHandle, UGASPAbilitySystemComponent*> ActiveGameplayEffectHandles;

	/** 
	 * Apply effects on overlap based on their application policies (applies to effects defined with ApplyOnOverlap).
	 */
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Effect Actor", Meta=(DisplayName="Apply Gameplay Effect On Overlap"))
	virtual void ApplyEffectsOnOverlap(AActor* InTargetActor);

	/** 
	 * Remove effects on overlap based on their removal policies (removes effects defined with RemoveOnOverlap).
	 */
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Effect Actor", Meta=(DisplayName="Remove Gameplay Effect On Overlap"))
	virtual void RemoveEffectsOnOverlap(AActor* InTargetActor);

	/** 
	 * Apply effects on end of overlap based on their application policies (applies to effects defined with ApplyOnEndOverlap).
	 */
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Effect Actor", Meta=(DisplayName="Apply Gameplay Effect On End Overlap"))
	virtual void ApplyEffectsOnEndOverlap(AActor* InTargetActor);

	/** 
	 * Remove effects on end of overlap based on their removal policies (removes effects defined with RemoveOnEndOverlap).
	 */
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Effect Actor", Meta=(DisplayName="Remove Gameplay Effect On End Overlap"))
	virtual void RemoveEffectsOnEndOverlap(AActor* InTargetActor);

private:

		
	/** Default root component for the actor */
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Effect Actor")
	TObjectPtr<USceneComponent> DefaultRootComponent;

	/** 
	 * Apply the specified gameplay effect to a target actor based on the provided effect info.
	 * This function handles the application logic for each effect.
	 */
	virtual void ApplyGameplayEffectToTarget(AActor* InTargetActor, const FGameplayEffectInfo& EffectInfo);

	/** 
	 * Remove the specified gameplay effect from a target actor based on the provided effect info.
	 */
	virtual void RemoveGameplayEffectFromTarget(AActor* InTargetActor, const FGameplayEffectInfo& EffectInfo);

	/**
	 * HandleEffects is the main helper function now. It handles both applying and removing effects based on a few parameters.
	 * @param InTargetActor 
	 * @param bApplyEffect 
	 * @param bIsEndOverlap 
	 */
	virtual void HandleEffects(AActor* InTargetActor, bool bApplyEffect, bool bIsEndOverlap);

};
