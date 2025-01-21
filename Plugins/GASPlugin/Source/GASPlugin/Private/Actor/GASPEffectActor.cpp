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

void AGASPEffectActor::ApplyGameplayEffectToTarget(AActor* InTargetActor, TSubclassOf<UGameplayEffect> InGameplayEffectClass)
{
	// Get the AbilitySystemComponent for the target actor
	UGASPAbilitySystemComponent* TargetAbilitySystemComponent = Cast<UGASPAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor));
	if (TargetAbilitySystemComponent == nullptr) return;
	ensureMsgf(InGameplayEffectClass, TEXT("Gameplay Effect Class is not set"));

	// Create a Gameplay Effect Context Handle for the target
	FGameplayEffectContextHandle GameplayEffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();

	// Add the source object (this actor) to the context; using a weak pointer ensures that the source object won't affect garbage collection
	GameplayEffectContextHandle.AddSourceObject(this);

	// Create the Gameplay Effect Spec Handle for the given Gameplay Effect Class
	// The second argument (1.f) is the level or magnitude of the effect (you may want to adjust this)
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(InGameplayEffectClass, 1.f, GameplayEffectContextHandle);

	// Apply the Gameplay Effect Spec to the target's Ability System Component
	// Note: The `Data` member of the GameplayEffectSpecHandle is a shared pointer to a Gameplay Effect Spec
	//       To pass it to ApplyGameplayEffectSpecToSelf(), we must dereference the shared pointer and pass it as a const reference.
	TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
}

