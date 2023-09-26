// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
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
	void	Activate(FEffectParameters Parameters);
private:
	double	_maxRange = 600.0;
	double	_minRange = 250.0;
	double	_lockMovementDuration = 0.12;
};
