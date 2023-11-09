#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "../Systems/HealthManager.h"
#include "../Systems/HealthManager.h"
#include "../Buffs/BuffMoltenShell.h"

#include "AbilityMoltenShell.generated.h"

#define BP_PATH_BUFFMOLTENSHELL		"/Game/TopDown/Blueprints/Actors/A_BuffMoltenShell"
#define BP_PATH_BUFFVAALMOLTENSHELL	"/Game/TopDown/Blueprints/Actors/A_BuffVaalMoltenShell"
#define BP_PATH_BUFFSTEELSKIN		"/Game/TopDown/Blueprints/Actors/A_BuffSteelskin"

UCLASS()
class FIRESTHOUSANDSUNS_API UGuardBase : public UAbility
{
	GENERATED_BODY()
public:
	UGuardBase();
	virtual bool	Activate(FEffectParameters Parameters, bool bCheckActivatable = false) override;

	double	HP = 1000;
	double	Absorbtion = 1.0;
	double	Duration = 5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABuffGuard>	BuffGuardClass;
private:
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilityMoltenShell : public UGuardBase
{
	GENERATED_BODY()
public:
	UAbilityMoltenShell();
	virtual bool	Activate(FEffectParameters Parameters, bool bCheckActivatable = false) override;
private:
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilityVaalMoltenShell : public UGuardBase
{
	GENERATED_BODY()
public:
	UAbilityVaalMoltenShell();
	virtual bool	Activate(FEffectParameters Parameters, bool bCheckActivatable = false) override;
private:
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilitySteelskin : public UGuardBase
{
	GENERATED_BODY()
public:
	UAbilitySteelskin();
	virtual bool	Activate(FEffectParameters Parameters, bool bCheckActivatable = false) override;
private:
};
