#include "AbilityManager.h"

constexpr int32	DEFAULT_SLOTS_AMOUNT = 5;

UAbilityManager::UAbilityManager() {
	this->_Slots.resize(DEFAULT_SLOTS_AMOUNT, nullptr);
}

void	UAbilityManager::SetSlotsAmount(int Amount) {
	this->_Slots.resize(std::max(0, Amount));
}

bool	UAbilityManager::SetAbility(int Index, UAbility* Ability) {
	if (Index < this->_Slots.size()) {
		this->_Slots[Index] = Ability;
		return true;
	} else {
		return false;
	}
}

UAbility* UAbilityManager::GetAbility(int Index) const {
	if (Index < this->_Slots.size()) {
		return this->_Slots[Index];
	} else {
		return nullptr;
	}
}

//template <class T>
//UAbility* UAbilityManager::GetAbility() const {
//	for (auto ability : this->_Slots) {
//		T* spe = Cast<T>(ability);
//		if (spe) {
//			return spe;
//		}
//	}
//	return nullptr;
//}

UAbility*	UAbilityManager::GetAbilityByClass(const TSubclassOf<UAbility> AbilityClass) const {
	UAbility* FoundAbility = nullptr;

	if (UClass* TargetClass = AbilityClass.Get()) {
		for (UAbility* Ability : this->_Slots) {
			if (Ability && Ability->IsA(TargetClass)) {
				return Ability;
			}
		}
	}

	return FoundAbility;
}

int		UAbilityManager::GetSlotsAmount() const { return this->_Slots.size(); }
