
#include "HealthManager.h"

UHealthManager::UHealthManager() {
}

UHealthManager::UHealthManager(double HP) : _maxhp(std::max(1.0, HP)), _hp(_maxhp) {
}

void	UHealthManager::CheckEmptyHP() const {
	if (this->_hp <= 0.0) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("[HealthManager] HP : %lf"), this->_hp));
		this->HpEmpty.Broadcast();
	}
}

void	UHealthManager::AddHP(double Value) {
	this->_hp = std::min(this->_hp + Value, this->_maxhp);
	this->HpChanged.Broadcast(this->_hp, this->_maxhp);
}
void	UHealthManager::RemoveHP(double Value) {
	this->_hp = std::max(this->_hp - Value, 0.0);
	this->HpChanged.Broadcast(this->_hp, this->_maxhp);
	this->CheckEmptyHP();
}
void	UHealthManager::SetHP(double Value) {
	this->_hp = std::min(Value, this->_maxhp);
	this->HpChanged.Broadcast(this->_hp, this->_maxhp);
	this->CheckEmptyHP();
}
void	UHealthManager::SetMaxHP(double Value) {
	this->_maxhp = Value;
	this->HpChanged.Broadcast(this->_hp, this->_maxhp);
}

double	UHealthManager::GetHP() const { return this->_hp; }
double	UHealthManager::GetMaxHP() const { return this->_maxhp;	}
