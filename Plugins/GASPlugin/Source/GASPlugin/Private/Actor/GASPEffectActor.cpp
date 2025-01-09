// Copyright Heathrow


#include "Actor/GASPEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/GASPAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AGASPEffectActor::AGASPEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	SetRootComponent(DefaultRootComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AGASPEffectActor::BeginPlay()
{
	Super::BeginPlay();

	// Binding custom functions to sphere components BeginOverlap and EndOverlap delegates.
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGASPEffectActor::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AGASPEffectActor::EndOverlap);
}

void AGASPEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor);
	if (AbilitySystemInterface)
	{
		const UGASPAttributeSet* GASPAttributeSet = Cast<UGASPAttributeSet>(AbilitySystemInterface->GetAbilitySystemComponent()->GetAttributeSet(UGASPAttributeSet::StaticClass()));
		UGASPAttributeSet* MutableGASPAttributeSet = const_cast<UGASPAttributeSet*>(GASPAttributeSet);
		MutableGASPAttributeSet->SetHealth(GASPAttributeSet->GetHealth() + 20.f);
		Destroy();
	}
}

void AGASPEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

