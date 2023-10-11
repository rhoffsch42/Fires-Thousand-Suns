// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "LifeFlask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ULifeFlask : public UAbility
{
	GENERATED_BODY()
public:
	ULifeFlask();
	virtual void	Activate(FEffectParameters Parameters) override;
protected:
	double	HealValue = 4500.0;
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API URubyFlask : public UAbility
{
	GENERATED_BODY()
public:
	URubyFlask();
	virtual void	Activate(FEffectParameters Parameters) override;
protected:
	double	LessFireDamage = 0.2;
	double	FireResistance = 0.5;
};
