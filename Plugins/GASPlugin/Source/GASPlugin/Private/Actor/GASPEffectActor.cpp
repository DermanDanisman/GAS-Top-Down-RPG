// Copyright Heathrow


#include "Actor/GASPEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GASPAbilitySystemComponent.h"

// Sets default values
AGASPEffectActor::AGASPEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	SetRootComponent(DefaultRootComponent);

}

// Called when the game starts or when spawned
void AGASPEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Apply the gameplay effect to the target actor based on its policy
void AGASPEffectActor::ApplyGameplayEffectToTarget(AActor* InTargetActor, const FGameplayEffectInfo& EffectInfo)
{
	// Get the AbilitySystemComponent for the target actor
	UGASPAbilitySystemComponent* TargetAbilitySystemComponent = Cast<UGASPAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor));
	if (TargetAbilitySystemComponent == nullptr) return;
	ensureMsgf(EffectInfo.GameplayEffectClass, TEXT("Gameplay Effect Class is not set"));
	
	// Create a Gameplay Effect Context Handle for the target
	FGameplayEffectContextHandle GameplayEffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();

	// Add the source object (this actor) to the context; using a weak pointer ensures that the source object won't affect garbage collection
	GameplayEffectContextHandle.AddSourceObject(this);

	// Create the Gameplay Effect Spec Handle for the given Gameplay Effect Class
	// The second argument (1.f) is the level or magnitude of the effect (you may want to adjust this)
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(EffectInfo.GameplayEffectClass, 1.f, GameplayEffectContextHandle);

	// Handle ApplyOnOverlap logic (you can check overlap conditions here)
	// Apply the Gameplay Effect Spec to the target's Ability System Component
	// Note: The `Data` member of the GameplayEffectSpecHandle is a shared pointer to a Gameplay Effect Spec
	//       To pass it to ApplyGameplayEffectSpecToSelf(), we must dereference the shared pointer and pass it as a const reference.
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

	// If it's an infinite effect, track it for later removal
	const bool bIsInfiniteGameplayEffect = GameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfiniteGameplayEffect && (EffectInfo.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap || EffectInfo.RemovalPolicy == EEffectRemovalPolicy::RemoveOnOverlap))
	{
		ActiveGameplayEffectHandles.Add(ActiveGameplayEffectHandle, TargetAbilitySystemComponent);
	}
}

// Apply effects when an overlap occurs
void AGASPEffectActor::ApplyEffectsOnOverlap(AActor* InTargetActor)
{
	// Iterate through the GameplayEffects array
	for (const FGameplayEffectInfo& EffectInfo : GameplayEffects)
	{
		// Check if the effect should be applied based on the application policy
		// For now, we apply all effects regardless of the policy, but you can check it here
		switch (EffectInfo.ApplicationPolicy)
		{
		case EEffectApplicationPolicy::ApplyOnOverlap:
			// Handle ApplyOnOverlap logic (you can check overlap conditions here)
				ApplyGameplayEffectToTarget(InTargetActor, EffectInfo);
			break;
		
		case EEffectApplicationPolicy::DoNotApply:
			// Skip this effect
				continue;

		default:
			break;
		}
	}
}

// Remove effects when an overlap occurs
void AGASPEffectActor::RemoveEffectsOnOverlap(AActor* InTargetActor)
{
	// Iterate through the GameplayEffects array
	for (const FGameplayEffectInfo& EffectInfo : GameplayEffects)
	{
		// Remove effects based on the removal policy
		if (EffectInfo.RemovalPolicy == EEffectRemovalPolicy::RemoveOnOverlap)
		{
			UGASPAbilitySystemComponent* TargetAbilitySystemComponent = Cast<UGASPAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor));
			if (TargetAbilitySystemComponent == nullptr) return;

			// Create a list of handles to remove
			TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandlesToRemove;

			// Loop through the active gameplay effects
			for (const auto& HandlePair : ActiveGameplayEffectHandles)
			{
				if (TargetAbilitySystemComponent == HandlePair.Value)
				{
					// Remove the gameplay effect
					TargetAbilitySystemComponent->RemoveActiveGameplayEffect(HandlePair.Key, 1);
					ActiveGameplayEffectHandlesToRemove.Add(HandlePair.Key);
				}
			}

			// Cleanup the map after removal
			for (const FActiveGameplayEffectHandle& HandleToRemove : ActiveGameplayEffectHandlesToRemove)
			{
				ActiveGameplayEffectHandles.Remove(HandleToRemove);
			}
		}
	}
}

// Apply effects when the overlap ends
void AGASPEffectActor::ApplyEffectsOnEndOverlap(AActor* InTargetActor)
{
	// Iterate through the GameplayEffects array
	for (const FGameplayEffectInfo& EffectInfo : GameplayEffects)
	{
		// Apply the effect if the policy matches
		if (EffectInfo.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyGameplayEffectToTarget(InTargetActor, EffectInfo);
		}
	}
}

// Remove effects when the overlap ends
void AGASPEffectActor::RemoveEffectsOnEndOverlap(AActor* InTargetActor)
{
	// Iterate through the GameplayEffects array
	for (const FGameplayEffectInfo& EffectInfo : GameplayEffects)
	{
		// Remove effects based on the removal policy
		if (EffectInfo.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			UGASPAbilitySystemComponent* TargetAbilitySystemComponent = Cast<UGASPAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor));
			if (TargetAbilitySystemComponent == nullptr) return;

			// Create a list of handles to remove
			TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandlesToRemove;

			// Loop through the active gameplay effects
			for (const auto& HandlePair : ActiveGameplayEffectHandles)
			{
				if (TargetAbilitySystemComponent == HandlePair.Value)
				{
					// Remove the gameplay effect
					TargetAbilitySystemComponent->RemoveActiveGameplayEffect(HandlePair.Key, 1);
					ActiveGameplayEffectHandlesToRemove.Add(HandlePair.Key);
				}
			}

			// Cleanup the map after removal
			for (const FActiveGameplayEffectHandle& HandleToRemove : ActiveGameplayEffectHandlesToRemove)
			{
				ActiveGameplayEffectHandles.Remove(HandleToRemove);
			}
		}
	}
}

