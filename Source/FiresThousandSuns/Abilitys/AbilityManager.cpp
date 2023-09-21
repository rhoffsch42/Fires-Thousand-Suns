#include "AbilityManager.h"

UAbilityManager::UAbilityManager() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	// You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	this->_slots.resize(DEFAULT_SLOTS_AMOUNT, nullptr);
}


// Called when the game starts
void UAbilityManager::BeginPlay() {
	Super::BeginPlay();
}

void	UAbilityManager::SetSlotsAmount(int Amount) {
	this->_slots.resize(std::max(0, Amount));
}

bool	UAbilityManager::SetAbility(int Index, UAbility* Ability) {
	if (Index < this->_slots.size()) {
		this->_slots[Index] = Ability;
		return true;
	} else {
		return false;
	}
}

int		UAbilityManager::GetSlotsAmount() const {
	return this->_slots.size();
}


// Called every frame
//void UAbilityManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

