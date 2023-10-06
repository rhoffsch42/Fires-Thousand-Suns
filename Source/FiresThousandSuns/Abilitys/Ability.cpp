#include "Ability.h"

UAbility::UAbility() {
	this->Cooldown = NewObject<UCooldown>();
	this->Cooldown->World = this->GetWorld();
}

void	UAbility::TryActivate(FEffectParameters Parameters) {
	if (this->Cooldown->IsReady()) {
		this->Activate(Parameters);
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("[Ability] failed to used, remaining : %lf sec"), this->Cooldown->Remaining()));
	}
}

void	UAbility::Activate(FEffectParameters Parameters) {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("[Ability] used ! CD:%d "), this->Cooldown->GetAvailableUses())
	);
	this->Cooldown->Use();
}
