#include "Cooldown.h"
#include "Kismet/GameplayStatics.h"

UCooldown::UCooldown() {}
UCooldown::UCooldown(UObject* WorldObject) : World(WorldObject) {}

bool	UCooldown::TryUse() {
	this->_update();
	if (this->_availableUses > 0) {
		this->Use();
		return true;
	} else {
		return false;
	}
}

void	UCooldown::Use() {
	this->_update();
	if (this->_availableUses == this->_maxUses)
		this->_lastUse = this->_safeGetTimeSeconds();
	this->_availableUses = std::max(0, this->_availableUses - 1);// should go negative if forced ?
}

void	UCooldown::Reset() {
	this->_availableUses = this->_maxUses;
	this->_lastUse = RESET_VALUE;
}

void	UCooldown::_update() {
	if (this->_availableUses < this->_maxUses) {
		double timeSeconds = this->_safeGetTimeSeconds();
		if (this->_duration == 0.0) {
			this->_availableUses = this->_maxUses;
			this->_lastUse = timeSeconds;
		} else {
			double availableUsesToAdd = (timeSeconds - this->_lastUse) / this->_duration;//could overflow if duration is really small...
			if ((int32)availableUsesToAdd >= 1) {
				this->_availableUses = std::min(this->_maxUses, this->_availableUses + (int32)availableUsesToAdd);
				this->_lastUse = timeSeconds;
			}
		}
	}
}

bool	UCooldown::IsReady() {
	this->_update();
	return (this->_availableUses > 0);
}

// seconds
double	UCooldown::Remaining() {
	this->_update();
	if (this->_availableUses < this->_maxUses) {
		return std::max(0.0, this->_duration - (this->_safeGetTimeSeconds() - this->_lastUse));
	} else {
		return 0.0;
	}
}

// percent normalized [0:1]
double	UCooldown::RemainingRelative() {
	if (this->_duration == 0.0) {
		return 0.0;
	} else {
		return (this->Remaining() / this->_duration);
	}
}

int32	UCooldown::GetAvailableUses() {
	this->_update();
	return this->_availableUses;
}

int32	UCooldown::GetMaxUses() const {
	return this->_maxUses;
}
void	UCooldown::SetMaxUses(const int32 Uses) {
	this->_maxUses = std::max(1, Uses);
}

void	UCooldown::SetDuration(const double Duration) {
	this->_duration = std::max(0.0, Duration);
}

double	UCooldown::GetDuration() const {
	return this->_duration;
}

double	UCooldown::_safeGetTimeSeconds() const {
	if (!this->World) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Cooldown::World is nullptr! Abort."));
		return -2;
	} else {
		return UGameplayStatics::GetTimeSeconds(this->World);
	}
}
