
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


/*
	sphere collision radius 45,0
	sphere mesh scale 1,2275
	ratation rate Y -137,5
*/
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ASun : public AActor
{
	GENERATED_BODY()
	
public:	
	ASun();
	UFUNCTION(BlueprintCallable)
	void	SetDestination(FVector Desto);
	UFUNCTION(BlueprintCallable)
	void	Move(float DeltaSeconds);
	UFUNCTION(BlueprintCallable)
	void	Explode();
	UFUNCTION(BlueprintCallable)
	bool	IsInRangeForMavenCancellation() const;
	UFUNCTION(BlueprintCallable)
	void	SetMavenCancellationDistanceThreshold(double Value); // range is [0:1]
	UFUNCTION(BlueprintCallable)
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
	virtual void Tick(float DeltaSeconds) override;

private:
	TObjectPtr<USceneComponent> _DefaultSceneRoot;
	FVector	_SpawnLocation;
	FVector	_Destination;
	double	_TotalTravelDistance = 1.0;
	double	_TimeBeforeMoving = 2.0;
	double	_Speed = 360.0;
	double	_Damage = 17355.0;//uber //16557.0 normal
	double	_ExplosionRadius = 300.0;
	double	_MavenCancellationDistanceThreshold = 0.15; // relative proportion of _travelDistance [0:1]

	void	_initComponents();
};
