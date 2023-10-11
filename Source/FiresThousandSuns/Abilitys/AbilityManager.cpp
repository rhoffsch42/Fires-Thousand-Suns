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
	if (Index < this->_Abilitys.Num()) {
		this->_Abilitys[Index] = Ability;
		return true;
	} else {
		return false;
	}
}

UAbility* UAbilityManager::GetAbility(int Index) const {
	if (Index < this->_Abilitys.Num()) {
		return this->_Abilitys[Index];
	}
	else {
		return nullptr;
	}
}

//template <class T>
//UAbility* UAbilityManager::GetAbility() const {
//	for (auto ability : this->_Abilitys) {
//		T* spe = Cast<T>(ability);
//		if (spe) {
//			return spe;
//		}
//	}
//	return nullptr;
//}

UAbility* UAbilityManager::GetAbilityByClass(const TSubclassOf<UAbility> AbilityClass) const {
	UAbility* FoundAbility = nullptr;

	if (UClass* TargetClass = AbilityClass.Get()) {
		for (UAbility* Ability : this->_Abilitys) {
			if (Ability && Ability->IsA(TargetClass)) {
				return Ability;
			}
		}
	}

	return FoundAbility;
}

UAbility* UAbilityManager::GetAbilityByType(const EAbilityType Type) const {
	UAbility* FoundAbility = nullptr;

	if (Type != EAbilityType::None) {
		for (UAbility* Ability : this->_Abilitys) {
			if (Ability && Ability->AbilityType == Type) {
				return Ability;
			}
		}
	}

	return FoundAbility;
}

int32		UAbilityManager::GetAbilityAmount() const { return this->_Abilitys.Num(); }
