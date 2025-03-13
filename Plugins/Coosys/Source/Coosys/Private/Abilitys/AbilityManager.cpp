#include "Abilitys/AbilityManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

constexpr int32	DEFAULT_SLOTS_AMOUNT = 5;

UAbilityManager::UAbilityManager() {
	this->_Abilitys.SetNum(DEFAULT_SLOTS_AMOUNT);
}

void	UAbilityManager::AddAbility(UAbility* Ability) {
	this->_Abilitys.Push(Ability);
	Ability->AbilityManager = this;
}

void	UAbilityManager::SetAbilityAmount(int Amount) {
	this->_Abilitys.SetNum(std::max(0, Amount));
}

bool	UAbilityManager::SetAbility(int Index, UAbility* Ability) {
	if (Index >= this->_Abilitys.Num()) {
		return false;
	}
	this->_Abilitys[Index] = Ability;
	Ability->AbilityManager = this;
	return true;
}

UAbility* UAbilityManager::GetAbility(int Index) const {
	if (Index >= this->_Abilitys.Num()) {
		return nullptr;
	}
	return this->_Abilitys[Index];
}

UAbility* UAbilityManager::GetAbilityByClass(const TSubclassOf<UAbility> AbilityClass) const {
	if (UClass* TargetClass = AbilityClass.Get()) {
		for (UAbility* Ability : this->_Abilitys) {
			if (Ability && Ability->IsA(TargetClass)) {
				return Ability;
			}
		}
	}
	return nullptr;
}

UAbility* UAbilityManager::GetAbilityByType(const EAbilityType Type) const {
	if (Type != EAbilityType::None) {
		for (UAbility* Ability : this->_Abilitys) {
			if (Ability && Ability->AbilityType == Type) {
				return Ability;
			}
		}
	}
	return nullptr;
}

int32		UAbilityManager::GetAbilityAmount() const { return this->_Abilitys.Num(); }


bool	UAbilityManager::SetCastedAbility(UAbility* Ability, const FEffectParameters& InParameters) {
	if (this->_bIsCasting || !Ability) {
		//DCOL(FColor::Purple, "SetCastedAbility() refused, already casting or supplied ability is null");
		return false;
	}

	this->_CastedAbility = Ability;
	this->_Parameters = InParameters;
	this->_bIsCasting = true;
	this->IncrementBlockInputCounter();
	//this->StopMovement();
	this->playerCtrl->StopMovement();

	FVector	location = InParameters.CursorHitLocation;
	location.Z = InParameters.ActorInstigator->GetActorLocation().Z;
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(
		InParameters.ActorInstigator->GetActorLocation(),
		location);
	InParameters.ActorInstigator->SetActorRotation(rot);
	//DCOL(FColor::Purple, FString::SanitizeFloat(Ability->CastTime->Remaining()).Append("s remaining until cast ends"));
	UKismetSystemLibrary::Delay(this->GetWorld(), Ability->CastTime->Remaining(),
		FLatentActionInfo(0, (int64)this, *FString("FinalizeCastedAbility"), this));
	return true;
}

void	UAbilityManager::FinalizeCastedAbility() {
	this->_CastedAbility->CastTime->Reset();// Delay() will not match perfectly the CastTime recharge, so we force reset to update _lastUse
	//DCOL(FColor::Purple, FString::SanitizeFloat(this->_CastedAbility->CastTime->Remaining()).Append(" (has just been reset by FinalizeCastedAbility())"));
	this->_CastedAbility->Activate(this->_Parameters);
	this->_CastedAbility = nullptr;
	this->_bIsCasting = false;
	this->DecrementBlockInputCounter();
}

void	UAbilityManager::IncrementBlockInputCounter() {
	this->_BlockInputCounter++;
	if (this->_BlockInputCounter > 0) {
		this->playerCtrl->bBlockInput = true;
	}
}

void	UAbilityManager::DecrementBlockInputCounter() {
	this->_BlockInputCounter--;
	if (this->_BlockInputCounter == 0) {
		this->playerCtrl->bBlockInput = false;
	}
	else if (this->_BlockInputCounter < 0) {
		//UFuncLib::CheckObject(nullptr, FString(__FUNCSIG__).Append(" BlockInputCounter is negative"));
	}
}

bool	UAbilityManager::GetIsCasting() const { return this->_bIsCasting; }


