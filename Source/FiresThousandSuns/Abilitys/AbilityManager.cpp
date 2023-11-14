#include "AbilityManager.h"

constexpr int32	DEFAULT_SLOTS_AMOUNT = 5;

UAbilityManager::UAbilityManager() {
	this->_Abilitys.SetNum(DEFAULT_SLOTS_AMOUNT);
}

void	UAbilityManager::AddAbility(UAbility* NewAbility) {
	this->_Abilitys.Push(NewAbility);
}

void	UAbilityManager::SetAbilityAmount(int Amount) {
	this->_Abilitys.SetNum(std::max(0, Amount));
}

bool	UAbilityManager::SetAbility(int Index, UAbility* Ability) {
	if (Index >= this->_Abilitys.Num()) {
		return false;
	}
	this->_Abilitys[Index] = Ability;
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
