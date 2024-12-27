// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GASCharacterBase.generated.h"

UCLASS(Abstract)
class GAS_TOPDOWNRPG_API AGASCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
};
