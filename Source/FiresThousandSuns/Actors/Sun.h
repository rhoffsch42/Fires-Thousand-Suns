// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sun.generated.h"

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSunExploded, FVector, SunLocation, double, Damage, double, ExplosionRadius);

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
	void	explode();

	// Delegate / event dispatcher
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FSunExploded SunExploded;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool	bIsMoving = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USceneComponent> _DefaultSceneRoot;
	FVector	_destination;
	double	_speed = 300.0;
	//double	_damage = 16557.0;//normal
	double	_damage = 17355.0;//uber
	double	_explosionRadius = 400.0;

	void	_initComponents();
};
