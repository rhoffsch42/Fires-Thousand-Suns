// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

#include "AbilityFlameDash.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilityFlameDash : public UAbility
{
	GENERATED_BODY()
public:
	UAbilityFlameDash();
	virtual void	PostInitProperties() override;
	virtual bool	IsActivatable(FEffectParameters Parameters) override;
	virtual bool	Activate(FEffectParameters Parameters, bool bCheckActivatable = false) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraSystem* NiagaraSystem = nullptr;
protected:
	double	_maxRange = 600.0;
	double	_minRange = 250.0;
	double	_lockMovementDuration = 0.12;
private:
	// calculated in IsActivatable(), used in Activate()
	FVector	_direction;
	double	_len;
	FVector	_targetDest;
	UNavigationSystemV1* _NavSys = nullptr;

};
