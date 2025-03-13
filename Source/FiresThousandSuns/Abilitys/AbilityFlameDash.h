#pragma once

#include "CoreMinimal.h"
#include "Abilitys/Ability.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

#include "AbilityFlameDash.generated.h"

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UGeneratedParametersFlameDash : public UGeneratedParameters
{
	GENERATED_BODY()
public:
	UGeneratedParametersFlameDash();
	FVector	Direction;
	double	Len = 0.0;
	FVector	TargetDest;
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilityFlameDash : public UAbility
{
	GENERATED_BODY()
public:
	UAbilityFlameDash();
	virtual void	PostInitProperties() override;

	virtual bool	IsActivatable(FEffectParameters& Parameters) override;
	virtual bool	Activate(FEffectParameters& Parameters) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraSystem* NiagaraSystem = nullptr;
protected:
	double	_maxRange = 600.0;
	double	_minRange = 250.0;
	double	_lockMovementDuration = 0.12;
private:
	UNavigationSystemV1* _NavSys = nullptr;
};
