// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/ActorComponent.h"
#include "GAS_ManagerComponent.generated.h"

/** Forward Declaration */
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASPLUGIN_API UGAS_ManagerComponent : public UActorComponent, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGAS_ManagerComponent();

	/** IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable, Category="GAS Plugin")
	void InitAbilityActorInfo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "GAS Plugin | Replication Mode")
	EGameplayEffectReplicationMode ReplicationMode = EGameplayEffectReplicationMode::Minimal;

	UPROPERTY(EditAnywhere, Category="GAS Plugin | Player State")
	TSubclassOf<APlayerState> OwnerPlayerState;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
};
