
#include "HealthManager.h"

UHealthManager::UHealthManager() {
}

UHealthManager::UHealthManager(double HP) : _maxhp(std::max(1.0, HP)), _hp(_maxhp) {
}

void	UHealthManager::CheckForDeath() {
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("[HealthManager] Player HP : %lf"), this->_hp));
	if (this->_hp <= 0) {
		this->OnNoHP();
	}
}

void	UHealthManager::OnNoHP() {
	this->HpEmpty.Broadcast();
}

void	UHealthManager::AddHP(double Value) {
	this->_hp = std::min(this->_hp + Value, this->_maxhp);
	this->HpChanged.Broadcast();
}
void	UHealthManager::RemoveHP(double Value) {
	this->_hp = std::max(this->_hp - Value, 0.0);
	this->HpChanged.Broadcast();
}
void	UHealthManager::SetHP(double Value) {
	this->_hp = std::min(Value, this->_maxhp);
	this->HpChanged.Broadcast();
}
void	UHealthManager::SetMaxHP(double Value) {
	this->_maxhp = Value;
	this->HpChanged.Broadcast();
}

double	UHealthManager::GetHP() const { return this->_hp; }
double	UHealthManager::GetMaxHP() const { return this->_maxhp;	}
