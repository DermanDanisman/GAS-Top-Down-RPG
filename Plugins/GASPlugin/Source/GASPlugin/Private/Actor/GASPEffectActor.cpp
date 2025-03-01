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
void AGASPEffectActor::ApplyGameplayEffectToTarget(AActor* InTargetActor, const FGameplayEffectActorInfo& EffectInfo)
{
	// Get the AbilitySystemComponent for the target actor
	UGASPAbilitySystemComponent* TargetAbilitySystemComponent = Cast<UGASPAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor));
	if (TargetAbilitySystemComponent == nullptr) return;
	ensureMsgf(EffectInfo.GameplayEffectClass, TEXT("Gameplay Effect Class is not set"));
	
	// Create a Gameplay Effect Context Handle for the target
	FGameplayEffectContextHandle GameplayEffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();

	// Add the source object (this actor) to the context; using a weak pointer ensures that the source object won't affect garbage collection
	GameplayEffectContextHandle.AddSourceObject(this);
	GameplayEffectContextHandle.Get()->SetEffectCauser(this);

	// Create the Gameplay Effect Spec Handle for the given Gameplay Effect Class
	// The second argument (1.f) is the level or magnitude of the effect (you may want to adjust this)
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(EffectInfo.GameplayEffectClass, EffectInfo.EffectActorLevel, GameplayEffectContextHandle);

	// Handle ApplyOnOverlap logic (you can check overlap conditions here)
	// Apply the Gameplay Effect Spec to the target's Ability System Component
	// Note: The `Data` member of the GameplayEffectSpecHandle is a shared pointer to a Gameplay Effect Spec
	//       To pass it to ApplyGameplayEffectSpecToSelf(), we must dereference the shared pointer and pass it as a const reference.
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

	if (EffectInfo.bDestroyActorOnEffectApplication) Destroy();

	// If it's an infinite effect, track it for later removal
	const bool bIsInfiniteGameplayEffect = GameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfiniteGameplayEffect && (EffectInfo.RemovalPolicy == EGameplayEEffectRemovalPolicy::RemoveOnEndOverlap || EffectInfo.RemovalPolicy == EGameplayEEffectRemovalPolicy::RemoveOnOverlap))
	{
		ActiveGameplayEffectHandles.Add(ActiveGameplayEffectHandle, TargetAbilitySystemComponent);
	}

	/*
	 * DEBUG: Count the active gameplay effects
	 */
	const int EffectCount = TargetAbilitySystemComponent->GetGameplayEffectCount(EffectInfo.GameplayEffectClass, TargetAbilitySystemComponent);
	const FString ClassName = EffectInfo.GameplayEffectClass->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("Active Effect Name and Count: %s and %d"), *ClassName, EffectCount));
}

void AGASPEffectActor::RemoveGameplayEffectFromTarget(AActor* InTargetActor, const FGameplayEffectActorInfo& EffectInfo)
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
			TargetAbilitySystemComponent->RemoveActiveGameplayEffect(HandlePair.Key, EffectInfo.StackRemovalCount);
			ActiveGameplayEffectHandlesToRemove.Add(HandlePair.Key);
		}
	}

	// Cleanup the map after removal
	for (const FActiveGameplayEffectHandle& HandleToRemove : ActiveGameplayEffectHandlesToRemove)
	{
		ActiveGameplayEffectHandles.Remove(HandleToRemove);
	}

	if (EffectInfo.bDestroyActorOnEffectRemoval) Destroy();

	/*
	 * DEBUG: Count the active gameplay effects
	 */
	const int EffectCount = TargetAbilitySystemComponent->GetGameplayEffectCount(EffectInfo.GameplayEffectClass, TargetAbilitySystemComponent);
	const FString ClassName = EffectInfo.GameplayEffectClass->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("Active Effect Name and Count: %s and %d"), *ClassName, EffectCount));
}

// Apply or Remove effects based on the provided action and policy type
void AGASPEffectActor::HandleEffects(AActor* InTargetActor, const bool bApplyEffect, const bool bIsEndOverlap)
{
	// Iterate through the GameplayEffects array
	for (const FGameplayEffectActorInfo& EffectInfo : GameplayEffects)
	{
		// Check if the action matches the effect's policy (Apply or Remove)
		if (bApplyEffect)
		{
			// Apply effects based on the application policy (ApplyOnOverlap or ApplyOnEndOverlap)
			if ((bIsEndOverlap && EffectInfo.ApplicationPolicy == EGameplayEffectApplicationPolicy::ApplyOnEndOverlap) ||
				(!bIsEndOverlap && EffectInfo.ApplicationPolicy == EGameplayEffectApplicationPolicy::ApplyOnOverlap))
			{
				ApplyGameplayEffectToTarget(InTargetActor, EffectInfo);
			}
		}
		else
		{
			// Remove effects based on the removal policy (RemoveOnOverlap or RemoveOnEndOverlap)
			if ((bIsEndOverlap && EffectInfo.RemovalPolicy == EGameplayEEffectRemovalPolicy::RemoveOnEndOverlap) ||
				(!bIsEndOverlap && EffectInfo.RemovalPolicy == EGameplayEEffectRemovalPolicy::RemoveOnOverlap))
			{
				RemoveGameplayEffectFromTarget(InTargetActor, EffectInfo);
			}
		}
	}
}

// Apply effects when an overlap occurs
void AGASPEffectActor::ApplyEffectsOnOverlap(AActor* InTargetActor)
{
	HandleEffects(InTargetActor, true, false); // true means applying, false means it's overlap (not end overlap)
}

// Remove effects when an overlap occurs
void AGASPEffectActor::RemoveEffectsOnOverlap(AActor* InTargetActor)
{
	HandleEffects(InTargetActor, false, false); // false means removing, false means it's overlap (not end overlap)
}

// Apply effects when the overlap ends
void AGASPEffectActor::ApplyEffectsOnEndOverlap(AActor* InTargetActor)
{
	HandleEffects(InTargetActor, true, true); // true means applying, true means it's end overlap
}

// Remove effects when the overlap ends
void AGASPEffectActor::RemoveEffectsOnEndOverlap(AActor* InTargetActor)
{
	HandleEffects(InTargetActor, false, true); // false means removing, true means it's end overlap
}

