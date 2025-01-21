// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASPEffectActor.generated.h"

/** Forward Declaration */

class UGameplayEffect;

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

	UPROPERTY(EditAnywhere, Category = "GASP Plugin | Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Effect Actor", Meta=(DisplayName="Apply Gameplay Effect To Target"))
	void ApplyGameplayEffectToTarget(AActor* InTarget, TSubclassOf<UGameplayEffect> InGameplayEffectClass);

protected:
	
	/** Default root component for the actor */
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Effect Actor")
	TObjectPtr<USceneComponent> DefaultRootComponent;

};
