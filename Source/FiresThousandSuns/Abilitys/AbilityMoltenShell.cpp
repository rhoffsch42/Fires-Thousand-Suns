
#include "AbilityMoltenShell.h"
#include "../FiresThousandSunsCharacter.h"
//class FiresThousandSunsCharacter;

#define SHELL_DURATION		3.6
#define CD_MAXUSES			1
#define CD_DURATION			4.0
#define SHELL_HP			5000.0 // max 5000
#define SHELL_ABSORBTION	0.75

UAbilityMoltenShell::UAbilityMoltenShell() {
	this->Cooldown->SetMaxUses(CD_MAXUSES);
	this->Cooldown->SetDuration(CD_DURATION + SHELL_DURATION); // This Skill's Cooldown does not recover during its effect
	this->Cooldown->Reset();

	this->HealthManager = NewObject<UHealthManager>();
	this->HealthManager->SetMaxHP(SHELL_HP);
	this->HealthManager->SetHP(0);
}

void	UAbilityMoltenShell::Activate(FEffectParameters Parameters) {
	this->UAbility::Activate(Parameters);

	this->HealthManager->SetHP(this->HealthManager->GetMaxHP());
	// spawn a Bonus/Buff with HPlifespan(this->_shellDuration)
}