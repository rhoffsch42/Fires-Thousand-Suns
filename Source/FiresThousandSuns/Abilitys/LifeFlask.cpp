
#include "LifeFlask.h"
#include "../FiresThousandSunsPlayerState.h"
#include "../FuncLib.h"

ULifeFlask::ULifeFlask() {
	this->AbilityType = EAbilityType::LifeFlask;
	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(6.0);
	this->Cooldown->Reset();
	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/flask-life-transparent_100x100_UIMat.flask-life-transparent_100x100_UIMat'"));
}

void	ULifeFlask::Activate(FEffectParameters Parameters) {
	for (auto target : Parameters.Targets) {
		AFiresThousandSunsPlayerState* state = Cast<AFiresThousandSunsPlayerState>(target);
		if (UFuncLib::CheckObject(state, "ULifeFlask::Activate() target is not player state")) {
			state->HealthManager->AddHP(this->HealValue);
		}
	}

	this->UAbility::Activate(Parameters);
}

/////////////////////////////////

URubyFlask::URubyFlask() {
	this->AbilityType = EAbilityType::RubyFlask;
	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(10.0);
	this->Cooldown->Reset();
	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/flask-fire-transparent_100x100_UIMat.flask-fire-transparent_100x100_UIMat'"));
}

void	URubyFlask::Activate(FEffectParameters Parameters) {
	for (auto target : Parameters.Targets) {
		// buff todo
	}

	this->UAbility::Activate(Parameters);
}
