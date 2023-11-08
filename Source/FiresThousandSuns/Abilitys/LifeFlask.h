
#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "LifeFlask.generated.h"


UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ULifeFlask : public UAbility
{
	GENERATED_BODY()
public:
	ULifeFlask();
	virtual void	PostInitProperties() override;

	virtual bool	Activate(FEffectParameters Parameters, bool bCheckActivatable = false) override;
protected:
	double	HealValue = 4000.0;
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API URubyFlask : public UAbility
{
	GENERATED_BODY()
public:
	URubyFlask();
	virtual void	PostInitProperties() override;
	virtual bool	Activate(FEffectParameters Parameters, bool bCheckActivatable = false) override;
protected:
	double	LessFireDamage = 0.2;
	double	FireResistance = 0.5;
};
