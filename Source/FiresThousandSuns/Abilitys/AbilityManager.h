// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Ability.h"

#include "AbilityManager.generated.h"

#define DEFAULT_SLOTS_AMOUNT	5

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRESTHOUSANDSUNS_API UAbilityManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityManager();
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void	SetSlotsAmount(int Amount);
	UFUNCTION(BlueprintCallable)
	bool	SetAbility(int Index, UAbility* Ability);
	UFUNCTION(BlueprintCallable)
	int		GetSlotsAmount() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	std::vector<UAbility*>	_slots;
};
