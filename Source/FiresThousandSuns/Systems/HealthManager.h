
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthManager.generated.h"


UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHpChanged, double, HP, double, MaxHP);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHpEmpty);

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UHealthManager : public UObject
{
	GENERATED_BODY()
public:	
	UHealthManager();
	UHealthManager(double HP);

	/* Do not call this with negative Value, there is no check for resulting negative HP. Use RemoveHP() for damaging */
	UFUNCTION(BlueprintCallable)
	void	AddHP(double Value);
	/* Do not call this with negative Value, there is no check for resulting HP > maxHP. Use AddHP() for healing */
	UFUNCTION(BlueprintCallable)
	void	RemoveHP(double Value);
	UFUNCTION(BlueprintCallable)
	void	SetHP(double Value);
	UFUNCTION(BlueprintCallable)
	void	SetMaxHP(double Value);
	UFUNCTION(BlueprintCallable)
	void	CheckEmptyHP() const;

	UFUNCTION(BlueprintCallable)
	double	GetHP() const;
	UFUNCTION(BlueprintCallable)
	double	GetMaxHP() const;

	// Delegate / event dispatcher
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FHpChanged	HpChanged;
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FHpEmpty	HpEmpty;

private:
	double	_maxhp = 100.0;
	double	_hp = 100.0;
};
