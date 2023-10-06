// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this component's properties
	UAbilityManager();
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void		SetAbilityAmount(int Amount);
	UFUNCTION(BlueprintCallable)
	bool		SetAbility(int Index, UAbility* Ability);
	UFUNCTION(BlueprintCallable)
	UAbility*	GetAbility(int Index) const;
	UFUNCTION(BlueprintCallable)
	UAbility*	GetAbilityByClass(const TSubclassOf<UAbility> AbilityClass) const;
	UFUNCTION(BlueprintCallable)
	int32		GetAbilityAmount() const;

protected:
	TArray<UAbility*>	_Abilitys;
private:
};
