// Copyright Heathrow


#include "AbilitySystem/GASPAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UGASPAttributeSet::UGASPAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(10.f);
	InitMaxMana(100.f);
	InitStamina(25.f);
	InitMaxStamina(50.f);
}

void UGASPAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/**
	 * DOREPLIFETIME_CONDITION_NOTIFY: This macro ensures that the attributes will be replicated when necessary, and it allows you to specify replication conditions.
	 * COND_None: This condition means the attribute is always replicated (there’s no special condition like COND_InitialOnly or COND_OwnerOnly).
	 * REPNOTIFY_Always: This ensures that the OnRep_* function is called every time the value changes.
	 * It triggers the relevant notification function regardless of whether the value changed on the server or client.
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, HealthRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, ManaRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASPAttributeSet, StaminaRegenRate, COND_None, REPNOTIFY_Always);
}

void UGASPAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), NewValue);
	}

	if (Attribute == GetMaxHealthAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Max Health: %f"), NewValue);
	}

	if (Attribute == GetHealthRegenRateAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Health Regen: %f"), NewValue);
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
		UE_LOG(LogTemp, Warning, TEXT("Mana: %f"), NewValue);
	}

	if (Attribute == GetMaxManaAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Max Mana: %f"), NewValue);
	}

	if (Attribute == GetManaRegenRateAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Mana Regen: %f"), NewValue);
	}
}

void UGASPAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
		UE_LOG(LogTemp, Warning, TEXT("Base Health: %f"), NewValue);
	}

	if (Attribute == GetMaxHealthAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Base Max Health: %f"), NewValue);
	}

	if (Attribute == GetHealthRegenRateAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Base Health Regen: %f"), NewValue);
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
		UE_LOG(LogTemp, Warning, TEXT("Base Mana: %f"), NewValue);
	}

	if (Attribute == GetMaxManaAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Base Max Mana: %f"), NewValue);
	}

	if (Attribute == GetManaRegenRateAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Base Mana Regen: %f"), NewValue);
	}
}

void UGASPAttributeSet::SetGameplayEffectProperties(const struct FGameplayEffectModCallbackData& Data,
	FGameplayEffectProperties& EffectProperties) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this Attribute Set)
	
	EffectProperties.GameplayEffectContextHandle = Data.EffectSpec.GetContext();
	EffectProperties.SourceAbilitySystemComponent = EffectProperties.GameplayEffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	// Capture source actor info
	if (IsValid(EffectProperties.SourceAbilitySystemComponent) && EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo.IsValid()
		&& EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.SourceAvatarActor = EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		EffectProperties.SourceController = EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
		if (EffectProperties.SourceController == nullptr && EffectProperties.SourceAvatarActor != nullptr)
		{
			if (const APawn* SourcePawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
			{
				EffectProperties.SourceController = SourcePawn->GetController();
			}
		}
		if (EffectProperties.SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController->GetPawn());
		}
	}

	// Capture target actor info
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
		UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
	}
}

void UGASPAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectProperties EffectProperties;
	SetGameplayEffectProperties(Data, EffectProperties);
}

void UGASPAttributeSet::OnRep_HealthChanged(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, Health, OldHealth);
}

void UGASPAttributeSet::OnRep_MaxHealthChanged(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, MaxHealth, OldMaxHealth);
}

void UGASPAttributeSet::OnRep_HealthRegenRateChanged(const FGameplayAttributeData& OldHealthRegenRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, HealthRegenRate, OldHealthRegenRate);
}

void UGASPAttributeSet::OnRep_ManaChanged(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, Mana, OldMana);
}

void UGASPAttributeSet::OnRep_MaxManaChanged(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, MaxMana, OldMaxMana);
}

void UGASPAttributeSet::OnRep_ManaRegenRateChanged(const FGameplayAttributeData& OldManaRegenRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, ManaRegenRate, OldManaRegenRate);
}

void UGASPAttributeSet::OnRep_StaminaChanged(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, Stamina, OldStamina);
}

void UGASPAttributeSet::OnRep_MaxStaminaChanged(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, MaxStamina, OldMaxStamina);
}

void UGASPAttributeSet::OnRep_StaminaRegenRateChanged(const FGameplayAttributeData& OldStaminaRegenRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASPAttributeSet, StaminaRegenRate, OldStaminaRegenRate);
}
