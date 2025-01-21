// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASPEffectActor.generated.h"

/** Forward Declaration */

class UGameplayEffect;


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
	 * TSubclassOf<UGameplayEffect> allows us to reference a subclass of UGameplayEffect.
	 * This property lets us define the Gameplay Effect that will be applied to targets.
	 * Set in the editor to specify which effect the actor will apply.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Applied Effects")
	TSubclassOf<UGameplayEffect> PeriodicGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP Plugin | Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	/** 
	 * ApplyGameplayEffectToTarget is a BlueprintCallable function that can be called to apply the defined Gameplay Effect 
	 * to a target actor. 
	 * The effect class and the target actor are provided as parameters.
	 */
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Effect Actor", Meta=(DisplayName="Apply Gameplay Effect To Target"))
	virtual void ApplyGameplayEffectToTarget(AActor* InTargetActor, TSubclassOf<UGameplayEffect> InGameplayEffectClass);

protected:
	
	/** Default root component for the actor */
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Effect Actor")
	TObjectPtr<USceneComponent> DefaultRootComponent;

};
