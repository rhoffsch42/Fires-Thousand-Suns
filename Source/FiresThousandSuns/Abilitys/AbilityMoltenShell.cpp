
#include "AbilityMoltenShell.h"
//#include "../FiresThousandSunsCharacter.h"
#include "../Buffs/BuffMoltenShell.h"
#include "../FuncLib.h"

constexpr int MOLTEN_SHELL_CD_MAXUSES = 1;
constexpr double MOLTEN_SHELL_CD_DURATION = 4.0;

// explicit instanciation
template ABuffMoltenShell* UFuncLib::SafeSpawnActor<ABuffMoltenShell>(
	UWorld* TheWorld,
	UClass* ActorClass,
	const FVector& Loc,
	const FRotator& Rot,
	//const bool      bNoCollisionFail,
	AActor* Owner,
	APawn* Instigator
);

UAbilityMoltenShell::UAbilityMoltenShell() {
	this->Cooldown->SetMaxUses(MOLTEN_SHELL_CD_MAXUSES);
	this->Cooldown->SetDuration(MOLTEN_SHELL_CD_DURATION + this->ShellDuration); // This Skill's Cooldown does not recover during its effect
	this->Cooldown->Reset();
}

void	UAbilityMoltenShell::Activate(FEffectParameters Parameters) {
	for (auto target : Parameters.Targets) {
		ABuffMoltenShell* buff = UFuncLib::SafeSpawnActor<ABuffMoltenShell>(Parameters.World, ABuffMoltenShell::StaticClass());
		if (this->ShellHP > 9000) { // ugly hardcode to differenciate from simple MoltenShell
			buff->BuffType = EBuffType::VaalMoltenShell;
		}
		buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
		buff->HealthManager->SetMaxHP(this->ShellHP);
		buff->HealthManager->SetHP(this->ShellHP);
		buff->SetBaseDuration(this->ShellDuration);
		buff->ApplyTo(target);
	}

	this->UAbility::Activate(Parameters);
}