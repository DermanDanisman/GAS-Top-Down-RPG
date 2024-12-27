// Copyright Heathrow


#include "Character/GASCharacterBase.h"

#include "Preferences/PersonaOptions.h"

// Sets default values
AGASCharacterBase::AGASCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AGASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

