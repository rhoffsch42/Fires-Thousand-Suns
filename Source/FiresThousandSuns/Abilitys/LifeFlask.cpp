
#include "LifeFlask.h"
#include "../FiresThousandSunsPlayerState.h"
#include "../Buffs/BuffRubyFlask.h"
#include "../FuncLib.h"
#include "Kismet/GameplayStatics.h"

ULifeFlask::ULifeFlask() {
	this->AbilityType = EAbilityType::LifeFlask;
	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(6.0);
	this->Cooldown->Reset();
	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/flask-life-transparent_100x100_UIMat.flask-life-transparent_100x100_UIMat'"));
	this->ActivationSuccessSoundCue = LoadObject<USoundCue>(this->GetWorld(),
		*FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/fts-flask_Cue.fts-flask_Cue'"));

	UFuncLib::CheckObject(this->ActivationSuccessSoundCue, "ULifeFlask::ULifeFlask() failed to LoadObject() USoundCue");
}

bool	ULifeFlask::Activate(FEffectParameters Parameters) {
	for (auto target : Parameters.Targets) {
		AFiresThousandSunsPlayerState* state = Cast<AFiresThousandSunsPlayerState>(target);
		if (UFuncLib::CheckObject(state, "ULifeFlask::Activate() target is not player state")) {
			state->HealthManager->AddHP(this->HealValue);
		} else { return false; }
	}

	return this->UAbility::Activate(Parameters);
}

/////////////////////////////////

URubyFlask::URubyFlask() {
	this->AbilityType = EAbilityType::RubyFlask;
	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(10.0);
	this->Cooldown->Reset();
	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/flask-fire-transparent_100x100_UIMat.flask-fire-transparent_100x100_UIMat'"));
	this->ActivationSuccessSoundCue = LoadObject<USoundCue>(this->GetWorld(),
		*FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/fts-flask_Cue.fts-flask_Cue'"));

	UFuncLib::CheckObject(this->ActivationSuccessSoundCue, "URubyFlask::URubyFlask() failed to LoadObject() USoundCue");
}

bool	URubyFlask::Activate(FEffectParameters Parameters) {
	for (auto target : Parameters.Targets) {
		ABuffRubyFlask* buff = UFuncLib::SafeSpawnActor<ABuffRubyFlask>(Parameters.World, ABuffRubyFlask::StaticClass());
		if (UFuncLib::CheckObject(buff, "URubyFlask::Activate() buff failed to create ")) {
			buff->SetBaseDuration(this->Cooldown->GetDuration());
			//buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
			buff->AttachToActor(target, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
			buff->ApplyTo(target);
		}
	}

	return this->UAbility::Activate(Parameters);
}
