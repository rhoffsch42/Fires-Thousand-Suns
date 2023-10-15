
#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "../Systems/HealthManager.h"
#include "../Systems/HealthManager.h"

#include "AbilityMoltenShell.generated.h"

UCLASS()
class FIRESTHOUSANDSUNS_API UGuardBase : public UAbility
{
	GENERATED_BODY()
public:
	UGuardBase();
	virtual void	Activate(FEffectParameters Parameters) override;

	double	HP = 1000;
	double	Absorbtion = 1.0;
	double	Duration = 5;
private:
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilityMoltenShell : public UGuardBase
{
	GENERATED_BODY()
public:
	UAbilityMoltenShell();
	virtual void	Activate(FEffectParameters Parameters) override;
private:
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilityVaalMoltenShell : public UGuardBase
{
	GENERATED_BODY()
public:
	UAbilityVaalMoltenShell();
	virtual void	Activate(FEffectParameters Parameters) override;
private:
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilitySteelskin : public UGuardBase
{
	GENERATED_BODY()
public:
	UAbilitySteelskin();
	virtual void	Activate(FEffectParameters Parameters) override;
private:
};
