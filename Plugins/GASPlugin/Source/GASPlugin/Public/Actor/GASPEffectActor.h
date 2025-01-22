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
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply,
};

/**
 * Enum for managing the removal policies for the gameplay effects.
 * Determines when and how the effects should be removed from a target.
 */
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnOverlap,
	RemoveOnEndOverlap,
	DoNotRemove,
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
		: ApplicationPolicy(EEffectApplicationPolicy::DoNotApply), RemovalPolicy(EEffectRemovalPolicy::DoNotRemove)
	{
	}

	FGameplayEffectInfo(const TSubclassOf<UGameplayEffect>& InEffectClass, const EEffectApplicationPolicy InApplicationPolicy, const EEffectRemovalPolicy InRemovalPolicy)
		: GameplayEffectClass(InEffectClass), ApplicationPolicy(InApplicationPolicy), RemovalPolicy(InRemovalPolicy)
	{}

	/** 
	 * TSubclassOf<UGameplayEffect> allows us to reference a subclass of UGameplayEffect.
	 * This property lets us define the Gameplay Effect that will be applied to targets.
	 * Set in the editor to specify which effect the actor will apply.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASP Plugin | Applied Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	// The policy for how and when the effect is applied
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASP Plugin | Applied Effects")
	EEffectApplicationPolicy ApplicationPolicy;

	// The policy for how and when the effect is removed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASP Plugin | Applied Effects")
	EEffectRemovalPolicy RemovalPolicy;
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

	// Flag to determine whether to destroy the actor after removing the effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Applied Effects")
	bool bDestroyOnEffectRemoval = false;

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
	 * Apply the specified gameplay effect to a target actor based on the provided effect info.
	 * This function handles the application logic for each effect.
	 */
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Effect Actor", Meta=(DisplayName="Apply Gameplay Effect To Target"))
	virtual void ApplyGameplayEffectToTarget(AActor* InTargetActor, const FGameplayEffectInfo& EffectInfo);

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

protected:
	
	/** Default root component for the actor */
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Effect Actor")
	TObjectPtr<USceneComponent> DefaultRootComponent;

};
