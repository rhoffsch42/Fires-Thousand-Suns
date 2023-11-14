#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ability.h"

#include "AbilityManager.generated.h"


/*
	Ability container with a desired size
*/
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilityManager : public UObject
{
	GENERATED_BODY()

public:	
	UAbilityManager();

	UFUNCTION(BlueprintCallable)
	void		AddAbility(UAbility* NewAbility);
	UFUNCTION(BlueprintCallable)
	void		SetAbilityAmount(int Amount);
	UFUNCTION(BlueprintCallable)
	bool		SetAbility(int Index, UAbility* Ability);
	UFUNCTION(BlueprintCallable)
	UAbility*	GetAbility(int Index) const;
	UFUNCTION(BlueprintCallable)
	UAbility*	GetAbilityByClass(const TSubclassOf<UAbility> AbilityClass) const;
	UFUNCTION(BlueprintCallable)
	UAbility* GetAbilityByType(const EAbilityType Type) const;
	UFUNCTION(BlueprintCallable)
	int32		GetAbilityAmount() const;

protected:
	TArray<UAbility*>	_Abilitys;
private:
};
