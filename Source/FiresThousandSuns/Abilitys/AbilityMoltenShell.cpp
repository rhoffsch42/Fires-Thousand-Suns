
#include "AbilityMoltenShell.h"
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
	this->Cooldown->SetDuration(1.0 + this->Duration); // This Skill's Cooldown does not recover during its effect
	this->Cooldown->Reset();
	this->TooltipName = "GuardBase";

	this->SetNewMaterial(this, FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/Default_UIMat.Default_UIMat'"));
	this->BuffGuardClass = ABuffGuard::StaticClass();
}

bool	UGuardBase::Activate(FEffectParameters& Parameters) {
	return Super::Activate(Parameters);
}

////////////////////////////////////

UAbilityMoltenShell::UAbilityMoltenShell() {
	this->AbilityType = EAbilityType::MoltenShell;
	this->HP = 5000.0;
	this->Absorbtion = 0.75;
	this->Duration = 3.6;

	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(4.0 + this->Duration); // This Skill's Cooldown does not recover during its effect
	this->Cooldown->Reset();
	this->TooltipName = "Molten Shield";

	ConstructorHelpers::FClassFinder<ABuffGuard> BuffClass(TEXT(BP_PATH_BUFFMOLTENSHELL));
	if (UFuncLib::CheckObject(BuffClass.Class, FSIG_APPEND(" failed to get Actor class ").Append(BP_PATH_BUFFMOLTENSHELL))) {
		this->BuffGuardClass = BuffClass.Class;
	} else {
		this->BuffGuardClass = ABuffMoltenShell::StaticClass();
	}

	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/FireShield_01_50x50_UIMat.FireShield_01_50x50_UIMat'"));
	this->ActivationSuccessSoundCue = LoadObject<USoundCue>(this->GetWorld(), *FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/fts-molten-shell_Cue.fts-molten-shell_Cue'"));

	UFuncLib::CheckObject(this->ActivationSuccessSoundCue, FSIG_APPEND(" failed to LoadObject() USoundCue"));
}

bool	UAbilityMoltenShell::Activate(FEffectParameters& Parameters) {
	for (auto target : Parameters.Targets) {
		ABuffMoltenShell* buff = UFuncLib::SafeSpawnActor<ABuffMoltenShell>(Parameters.World, this->BuffGuardClass);
		if (UFuncLib::CheckObject(buff, FSIG_APPEND(" failed to create buff with SafeSpawnActor()"))) {
			buff->Absorption = this->Absorbtion;
			buff->HealthManager->SetMaxHP(this->HP);
			buff->HealthManager->SetHP(this->HP);
			buff->IconMaterial = this->IconMaterial;
			buff->SetBaseDuration(this->Duration);
			buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
			buff->ApplyTo(target);
		}
	}

	return Super::Activate(Parameters);
}

////////////////////////////////////

UAbilityVaalMoltenShell::UAbilityVaalMoltenShell() {
	this->AbilityType = EAbilityType::VaalMoltenShell;
	this->HP = 10000.0;
	this->Absorbtion = 0.39;
	this->Duration = 10.8;

	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(50.0 + this->Duration); // This Skill's Cooldown does not recover during its effect
	this->Cooldown->Reset();
	this->TooltipName = "Lava Molten Shield";

	ConstructorHelpers::FClassFinder<ABuffGuard> BuffClass(TEXT(BP_PATH_BUFFVAALMOLTENSHELL));
	if (UFuncLib::CheckObject(BuffClass.Class, FSIG_APPEND(" failed to get Actor class ").Append(BP_PATH_BUFFVAALMOLTENSHELL))) {
		this->BuffGuardClass = BuffClass.Class;
	} else {
		this->BuffGuardClass = ABuffVaalMoltenShell::StaticClass();
	}

	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/FireShield_red_01_50x50_UIMat.FireShield_red_01_50x50_UIMat'"));
	this->ActivationSuccessSoundCue = LoadObject<USoundCue>(this->GetWorld(), *FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/fts-molten-shell_Cue.fts-molten-shell_Cue'"));

	UFuncLib::CheckObject(this->ActivationSuccessSoundCue, FSIG_APPEND(" failed to LoadObject() USoundCue"));
}

bool	UAbilityVaalMoltenShell::Activate(FEffectParameters& Parameters) {
	for (auto target : Parameters.Targets) {
		ABuffVaalMoltenShell* buff = UFuncLib::SafeSpawnActor<ABuffVaalMoltenShell>(Parameters.World, this->BuffGuardClass);
		if (UFuncLib::CheckObject(buff, FSIG_APPEND(" failed to create buff with SafeSpawnActor()"))) {
			buff->Absorption = this->Absorbtion;
			buff->HealthManager->SetMaxHP(this->HP);
			buff->HealthManager->SetHP(this->HP);
			buff->IconMaterial = this->IconMaterial;
			buff->SetBaseDuration(this->Duration);
			buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
			buff->ApplyTo(target);
		}
	}

	return Super::Activate(Parameters);
}

////////////////////////////////////

UAbilitySteelskin::UAbilitySteelskin() {
	this->AbilityType = EAbilityType::Steelskin;
	this->HP = 2209.0;
	this->Absorbtion = 0.70;
	this->Duration = 1.5;

	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(4.05 + this->Duration); // This Skill's Cooldown does not recover during its effect
	this->Cooldown->Reset();
	this->TooltipName = "Iron Skin";

	ConstructorHelpers::FClassFinder<ABuffGuard> BuffClass(TEXT(BP_PATH_BUFFSTEELSKIN));
	if (UFuncLib::CheckObject(BuffClass.Class, FSIG_APPEND(" failed to get Actor class ").Append(BP_PATH_BUFFSTEELSKIN))) {
		this->BuffGuardClass = BuffClass.Class;
	} else {
		this->BuffGuardClass = ABuffSteelskin::StaticClass();
	}

	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/aura_100x100_UIMat.aura_100x100_UIMat'"));
	this->ActivationSuccessSoundCue = LoadObject<USoundCue>(this->GetWorld(), *FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/fts-steelskin_Cue.fts-steelskin_Cue'"));

	UFuncLib::CheckObject(this->ActivationSuccessSoundCue, FSIG_APPEND(" failed to LoadObject() USoundCue"));
}

bool	UAbilitySteelskin::Activate(FEffectParameters& Parameters) {
	for (auto target : Parameters.Targets) {
		ABuffSteelskin* buff = UFuncLib::SafeSpawnActor<ABuffSteelskin>(Parameters.World, this->BuffGuardClass);
		if (UFuncLib::CheckObject(buff, FSIG_APPEND(" failed to create buff with SafeSpawnActor()"))) {
			buff->Absorption = this->Absorbtion;
			buff->HealthManager->SetMaxHP(this->HP);
			buff->HealthManager->SetHP(this->HP);
			buff->IconMaterial = this->IconMaterial;
			buff->SetBaseDuration(this->Duration);
			buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
			buff->ApplyTo(target);
		}
	}

	return Super::Activate(Parameters);
}
