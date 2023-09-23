// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "../Systems/HealthManager.h"
#include "../Systems/HealthManager.h"

#include "AbilityMoltenShell.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilityMoltenShell : public UAbility
{
	GENERATED_BODY()
public:
	UAbilityMoltenShell();
	void	Activate(FEffectParameters Parameters);

	double	ShellHP = 5000.0;
	double	ShellAbsorbtion = 0.75;
	double	ShellDuration = 3.6;
private:
};
