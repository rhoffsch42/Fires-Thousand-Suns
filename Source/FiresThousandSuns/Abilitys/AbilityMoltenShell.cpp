
#include "AbilityMoltenShell.h"
//#include "../FiresThousandSunsCharacter.h"
#include "../Buffs/BuffMoltenShell.h"
#include "../FuncLib.h"

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

////////////////////////////////////

UGuardBase::UGuardBase() {
	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(1.0 + this->ShellDuration); // This Skill's Cooldown does not recover during its effect
	this->Cooldown->Reset();
	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/Default_UIMat.Default_UIMat'"));
}

void	UGuardBase::Activate(FEffectParameters Parameters) {
	this->UAbility::Activate(Parameters);
}

////////////////////////////////////

UAbilityMoltenShell::UAbilityMoltenShell() {
	this->AbilityType = EAbilityType::MoltenShell;
	this->ShellHP = 5000.0;
	this->ShellAbsorbtion = 0.75;
	this->ShellDuration = 3.6;

	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(4.0 + this->ShellDuration); // This Skill's Cooldown does not recover during its effect
	this->Cooldown->Reset();
	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/FireShield_01_50x50_UIMat.FireShield_01_50x50_UIMat'"));
}

void	UAbilityMoltenShell::Activate(FEffectParameters Parameters) {
	for (auto target : Parameters.Targets) {
		ABuffMoltenShell* buff = UFuncLib::SafeSpawnActor<ABuffMoltenShell>(Parameters.World, ABuffMoltenShell::StaticClass());
		buff->BuffType = EBuffType::MoltenShell;
		buff->ShellAbsorption = this->ShellAbsorbtion;
		buff->HealthManager->SetMaxHP(this->ShellHP);
		buff->HealthManager->SetHP(this->ShellHP);
		buff->SetBaseDuration(this->ShellDuration);
		buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
		buff->ApplyTo(target);
	}

	this->UGuardBase::Activate(Parameters);
}

////////////////////////////////////

UAbilityVaalMoltenShell::UAbilityVaalMoltenShell() {
	this->AbilityType = EAbilityType::VaalMoltenShell;
	this->ShellHP = 10000.0;
	this->ShellAbsorbtion = 0.39;
	this->ShellDuration = 10.8;

	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(50.0 + this->ShellDuration); // This Skill's Cooldown does not recover during its effect
	this->Cooldown->Reset();
	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/FireShield_red_01_50x50_UIMat.FireShield_red_01_50x50_UIMat'"));
}

void	UAbilityVaalMoltenShell::Activate(FEffectParameters Parameters) {
	for (auto target : Parameters.Targets) {
		ABuffMoltenShell* buff = UFuncLib::SafeSpawnActor<ABuffMoltenShell>(Parameters.World, ABuffMoltenShell::StaticClass());
		buff->BuffType = EBuffType::VaalMoltenShell;
		buff->ShellAbsorption = this->ShellAbsorbtion;
		buff->HealthManager->SetMaxHP(this->ShellHP);
		buff->HealthManager->SetHP(this->ShellHP);
		buff->SetBaseDuration(this->ShellDuration);
		buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
		buff->ApplyTo(target);
	}

	this->UGuardBase::Activate(Parameters);
}

////////////////////////////////////

UAbilitySteelskin::UAbilitySteelskin() {
	this->AbilityType = EAbilityType::Steelskin;
	this->ShellHP = 2209.0;
	this->ShellAbsorbtion = 0.70;
	this->ShellDuration = 1.5;

	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(4.05 + this->ShellDuration); // This Skill's Cooldown does not recover during its effect
	this->Cooldown->Reset();
	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/aura_100x100_UIMat.aura_100x100_UIMat'"));
}

void	UAbilitySteelskin::Activate(FEffectParameters Parameters) {
	for (auto target : Parameters.Targets) {
		ABuffMoltenShell* buff = UFuncLib::SafeSpawnActor<ABuffMoltenShell>(Parameters.World, ABuffMoltenShell::StaticClass());
		buff->BuffType = EBuffType::Steelskin;
		buff->ShellAbsorption = this->ShellAbsorbtion;
		buff->HealthManager->SetMaxHP(this->ShellHP);
		buff->HealthManager->SetHP(this->ShellHP);
		buff->SetBaseDuration(this->ShellDuration);
		buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
		buff->ApplyTo(target);
	}

	this->UGuardBase::Activate(Parameters);
}