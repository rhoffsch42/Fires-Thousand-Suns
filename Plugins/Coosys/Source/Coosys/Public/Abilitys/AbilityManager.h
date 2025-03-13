#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Abilitys/Ability.h"

#include "AbilityManager.generated.h"


/*
	TODO:
		- refacto this as an ActorComponent
		- migrate FTSPlayerController::SetCastedAbility to this
		- migrate FTSPlayerController::FinalizeCastedAbility to this
		- migrate FTSPlayerController::IncrementBlockInputCounter to this
		- migrate FTSPlayerController::DecrementBlockInputCounter to this
		- migrate FTSPlayerController::GetIsCasting to this

		- FTSPlayerController add and use the component

	TMP before refacto:
		- store PlayerController in a variable in the current class
		- use the variable in the functions

*/

/*
	Ability container with a desired size
*/
UCLASS(Blueprintable)
class COOSYS_API UAbilityManager : public UObject
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
	UAbility*	GetAbilityByType(const EAbilityType Type) const;
	UFUNCTION(BlueprintCallable)
	int32		GetAbilityAmount() const;


	// PlayerController casting
	UFUNCTION(BlueprintCallable)
	bool	SetCastedAbility(UAbility* Ability, const FEffectParameters& InParameters);
	UFUNCTION(BlueprintCallable)
	void	FinalizeCastedAbility();
	UFUNCTION(BlueprintCallable)
	void	IncrementBlockInputCounter();
	UFUNCTION(BlueprintCallable)
	void	DecrementBlockInputCounter();

	UFUNCTION(BlueprintCallable)
	bool	GetIsCasting() const;

	// TMP
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APlayerController* playerCtrl = nullptr;

protected:
	TArray<UAbility*>	_Abilitys;
private:
	int32				_BlockInputCounter = 0; // FIX: this behavior is isolated from everything else. Anything affecting APlayerController::bBlockInput will interfere with this 
	UAbility*			_CastedAbility;
	FEffectParameters	_Parameters;
	bool				_bIsCasting = false;
};
