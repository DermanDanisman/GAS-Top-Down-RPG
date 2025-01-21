// Copyright Heathrow


#include "Character/TDCharacterBase.h"

ATDCharacterBase::ATDCharacterBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATDCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ATDCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void ATDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
