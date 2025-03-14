#pragma once

#include "CoreMinimal.h"
#include "Abilitys/Ability.h"
#include "../Buffs/BuffRubyFlask.h"

#include "LifeFlask.generated.h"

#define BP_PATH_BUFFRUBYFLASK	"/Game/TopDown/Blueprints/Actors/A_BuffRubyFlask"

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ULifeFlask : public UAbility
{
	GENERATED_BODY()
public:
	ULifeFlask();
	virtual void	PostInitProperties() override;

	virtual bool	Activate(FEffectParameters& Parameters) override;
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
	virtual bool	Activate(FEffectParameters& Parameters) override;
protected:
	double	LessFireDamage = 0.2;
	double	FireResistance = 0.5;
	TSubclassOf<ABuffRubyFlask>	_BuffClass;
};
