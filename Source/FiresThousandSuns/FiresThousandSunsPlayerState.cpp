
#include "FiresThousandSunsPlayerState.h"
#include "FiresThousandSunsGameInstance.h"
#include "Systems/HealthManager.h"
#include "Abilitys/LifeFlask.h"
#include "Abilitys/AbilityFlameDash.h"
#include "Abilitys/AbilityMoltenShell.h"

#include "FuncLib.h"

constexpr float D_LEN = 5.0f;
void	AFiresThousandSunsPlayerState::PrintStatistics(const FPlayerStatistics& Stats) {
	if (GEngine) {
		D_(GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(
			TEXT("Movement Speed          : %d\n"
				"Life                    : %d\n"
				"Life Regeneration       : %d\n"
				"Fire Resistance         : %d\n"
				"Spell Supression Chance : %d\n"
				"Spell Supression Effect : %d\n"
				"Fortify Stacks          : %d\n"),
			Stats.MovementSpeed,
			Stats.Life,
			Stats.LifeRegeneration,
			Stats.FireResistance,
			Stats.SpellSuppressionChance,
			Stats.SpellSuppressionEffect,
			Stats.FortifyEffect
		)));
	}
}

AFiresThousandSunsPlayerState::AFiresThousandSunsPlayerState() {
	this->_InitPreBeginPlay();
}

void	AFiresThousandSunsPlayerState::_InitPreBeginPlay() {
	// Buffs
	this->BuffManager = CreateDefaultSubobject<UBuffManager>(TEXT("BuffManager"));
	// must be built in the constructor, has to be done in a valid world (when the owner has a world)
	
	// HealthManager
	this->HealthManager = NewObject<UHealthManager>(this, GEN_UNAME(this));
	this->HealthManager->SetMaxHP(this->PlayerStatistics.Life);
	this->HealthManager->SetHP(this->PlayerStatistics.Life);

	// Abilitys
	auto FlameDash = NewObject<UAbilityFlameDash>(this, GEN_UNAME(this));
	auto MoltenShell = NewObject<UAbilityMoltenShell>(this, GEN_UNAME(this));
	auto VaalMoltenShell = NewObject<UAbilityVaalMoltenShell>(this, GEN_UNAME(this));
	auto Steelskin = NewObject<UAbilitySteelskin>(this, GEN_UNAME(this));

	this->AbilityManager = NewObject<UAbilityManager>(this, GEN_UNAME(this));
	this->AbilityManager->SetAbilityAmount(5);
	this->AbilityManager->SetAbility(0, nullptr); // used as a 'slot clearer'
	this->AbilityManager->SetAbility(1, FlameDash);
	this->AbilityManager->SetAbility(2, Steelskin);
	this->AbilityManager->SetAbility(3, MoltenShell);
	this->AbilityManager->SetAbility(4, VaalMoltenShell);
	//this->AbilityManager->SetAbility(5, VaalArcticArmor);
	// shieldCharge // /Script/Engine.Material'/Game/LevelPrototyping/Materials/shield-bash_100x100_UIMat.shield-bash_100x100_UIMat'

	// Flask
	auto LifeFlask = NewObject<ULifeFlask>(this, GEN_UNAME(this));
	auto RubyFlask = NewObject<URubyFlask>(this, GEN_UNAME(this));

	this->FlaskManager = NewObject<UAbilityManager>(this, GEN_UNAME(this));
	this->FlaskManager->SetAbilityAmount(5);
	this->FlaskManager->SetAbility(0, nullptr); // used as a 'slot clearer'
	this->FlaskManager->SetAbility(1, LifeFlask);
	this->FlaskManager->SetAbility(2, RubyFlask);
	this->FlaskManager->SetAbility(3, nullptr);
	this->FlaskManager->SetAbility(4, nullptr);
}

void	AFiresThousandSunsPlayerState::_InitPostBeginPlay() {
	// Buffs
	this->AddOwnedComponent(this->BuffManager);
	//this->BuffManager->RegisterComponent();
}

 void AFiresThousandSunsPlayerState::BeginPlay() {
	 Super::BeginPlay();

	 this->_InitPostBeginPlay();

	 // Check Cooldowns Worlds
	 int32 count = this->AbilityManager->GetAbilityAmount();
	 for (int32 i = 0; i < count; i++) {
		 auto ability = this->AbilityManager->GetAbility(i);
		 if (ability) {
			 UFuncLib::CheckObject(ability->Cooldown->World, FSIG_APPEND(" Missing Cooldown->World on ability"));
			 UFuncLib::CheckObject(ability->CastTime->World, FSIG_APPEND(" Missing CastTime->World on ability"));
		 }

	 }
}
