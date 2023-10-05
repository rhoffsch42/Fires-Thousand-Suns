// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sun.generated.h"

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSunExploded, FVector, SunLocation, double, Damage, double, ExplosionRadius);
UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSunMavenCancelled);

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ASun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASun();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void	SetDestination(FVector Desto);
	UFUNCTION(BlueprintCallable)
	void	Move(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	void	Explode();
	UFUNCTION(BlueprintCallable)
	bool	IsInRangeForMavenCancellation() const;
	UFUNCTION(BlueprintCallable)
	void	SetMavenCancellationDistanceThreshold(double Value); // range is [0:1]
	double	GetMavenCancellationDistanceThreshold() const;
	UFUNCTION(BlueprintCallable)
	void	SetDamage(double Value);
	UFUNCTION(BlueprintCallable)
	double	GetDamage(double Value) const;

	// Delegates / events dispatcher
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FSunExploded SunExploded;
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FSunMavenCancelled SunMavenCancelled;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool	bIsMoving = false;
	bool	bMavenCancelled = false;
protected:
	virtual void BeginPlay() override;

private:
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USceneComponent> _DefaultSceneRoot;
	FVector	_spawnLocation;
	FVector	_destination;
	double	_totalTravelDistance = 1.0;
	double	_timeBeforeMoving = 2.0;
	double	_speed = 360.0;
	double	_damage = 17355.0;//uber //16557.0 normal
	double	_explosionRadius = 400.0;
	double	_mavenCancellationDistanceThreshold = 0.15; // relative proportion of _travelDistance [0:1]

	void	_initComponents();
};
