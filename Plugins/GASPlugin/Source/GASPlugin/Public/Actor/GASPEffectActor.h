// Copyright Heathrow

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASPEffectActor.generated.h"

/** Forward Declaration */
class USphereComponent;

UCLASS()
class GASPLUGIN_API AGASPEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGASPEffectActor();

	
	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Effect Actor | Sphere Component")
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "GASP Plugin | Effect Actor | Sphere Component")
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Default root component for the actor */
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Effect Actor")
	TObjectPtr<USceneComponent> DefaultRootComponent;

	/** Static mesh component representing the visual part of the effect actor */
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Effect Actor")
	TObjectPtr<UStaticMeshComponent> Mesh;

	/** Sphere component for detecting overlaps with other actors */
	UPROPERTY(VisibleAnywhere, Category = "GASP Plugin | Effect Actor")
	TObjectPtr<USphereComponent> SphereComponent;

};
