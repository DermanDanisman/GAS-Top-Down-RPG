// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GASPCharacter.generated.h"

/** Forward Declaration */
class UAbilitySystemComponent;
class UAttributeSet;

// A structure that holds different configurations for movement behavior.
USTRUCT(BlueprintType)
struct FCharacterMovementConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Movement Config")
	bool bOrientRotationToMovement = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Movement Config")
	FRotator RotationRate = FRotator(0.0f, 450.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Movement Config")
	bool bConstrainToPlane = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Movement Config")
	bool bSnapToPlaneAtStart = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Movement Config")
	bool bUseControllerRotationPitch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Movement Config")
	bool bUseControllerRotationYaw = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Movement Config")
	bool bUseControllerRotationRoll = false;

	// You can add more camera-related settings here
};

UCLASS(Abstract)
class GASPLUGIN_API AGASPCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASPCharacter();
	void InitAbilityActorInfo();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Ability System Interface */
	// Get the Ability System Component for this character (used for managing abilities, effects, etc.)
	UFUNCTION(BlueprintCallable, Category="GASP Plugin | Ability System")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Get the Attribute Set for this character (holds player attributes like health, mana, etc.)
	UFUNCTION(BlueprintCallable, Category="GASP Plugin | Ability System")
	virtual UAttributeSet* GetAttributeSetComponent() const;
	/** end Ability System Interface */

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** Movement configurations */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASP Plugin | Movement Config", meta = (Tooltip = "Call ApplyMovementConfig() to apply this structure."))
	FCharacterMovementConfig MovementConfig;
	// Applies movement configuration settings from the MovementConfig structure to the character's movement component.
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Movement Config", meta = (Tooltip = "Applies movement configuration settings from the MovementConfig structure to the character's movement component."))
	void ApplyMovementConfig();
	/** end Movement configurations */

	/** Ability System */
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditAnywhere, Category = "GASP Plugin | Ability System")
	EGameplayEffectReplicationMode GameplayEffectReplicationMode = EGameplayEffectReplicationMode::Minimal;
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;
	// Initializes the Ability System Component and Attribute Set for the character, and configures replication settings for multiplayer.
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Ability System", meta = (Tooltip = "Initializes the Ability System Component and Attribute Set for the character, and configures replication settings for multiplayer."))
	void InitializeAbilitySystem();
	/** end Ability System */
};
