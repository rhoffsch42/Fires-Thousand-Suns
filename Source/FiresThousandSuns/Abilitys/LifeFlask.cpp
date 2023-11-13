#include "LifeFlask.h"
#include "../FiresThousandSunsPlayerState.h"
#include "../FuncLib.h"
#include "Kismet/GameplayStatics.h"

ULifeFlask::ULifeFlask() {
	this->AbilityType = EAbilityType::LifeFlask;
	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(6.0);
	this->Cooldown->Reset();
	this->TooltipName = "Life Flask";

	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/flask-life-transparent_100x100_UIMat.flask-life-transparent_100x100_UIMat'"));
	this->ActivationSuccessSoundCue = LoadObject<USoundCue>(this->GetWorld(),
		*FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/fts-flask_Cue.fts-flask_Cue'"));

}

void	ULifeFlask::PostInitProperties() {
	Super::PostInitProperties();

	UFuncLib::CheckObject(this->ActivationSuccessSoundCue, "ULifeFlask::ULifeFlask() failed to LoadObject() USoundCue");
}

bool	ULifeFlask::Activate(FEffectParameters& Parameters) {
	for (auto target : Parameters.Targets) {
		AFiresThousandSunsPlayerState* state = Cast<AFiresThousandSunsPlayerState>(target);
		if (UFuncLib::CheckObject(state, "ULifeFlask::Activate() target is not player state")) {
			state->HealthManager->AddHP(this->HealValue);
		}
		else { return false; }
	}

	return Super::Activate(Parameters);
	//return this->UAbility::Activate(Parameters);
}

/////////////////////////////////

URubyFlask::URubyFlask() {
	this->AbilityType = EAbilityType::RubyFlask;
	this->Cooldown->SetMaxUses(1);
	this->Cooldown->SetDuration(15.0);
	this->Cooldown->Reset();
	this->TooltipName = "Ruby Flask";

	ConstructorHelpers::FClassFinder<ABuffRubyFlask> BuffClass(TEXT(BP_PATH_BUFFRUBYFLASK));
	if (UFuncLib::CheckObject(BuffClass.Class, FSIG_APPEND(" failed to get Actor class ").Append(BP_PATH_BUFFRUBYFLASK))) {
		UFuncLib::CheckObject(BuffClass.Class, FSIG_APPEND(" BuffClass.Class is null"));
		this->_BuffClass = BuffClass.Class;
	}
	else {
		this->_BuffClass = ABuffRubyFlask::StaticClass();
	}

	this->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/flask-fire-transparent_100x100_UIMat.flask-fire-transparent_100x100_UIMat'"));
	this->ActivationSuccessSoundCue = LoadObject<USoundCue>(this->GetWorld(),
		*FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/fts-flask_Cue.fts-flask_Cue'"));
}

void	URubyFlask::PostInitProperties() {
	Super::PostInitProperties();

	UFuncLib::CheckObject(this->ActivationSuccessSoundCue, FSIG_APPEND(" failed to LoadObject() USoundCue"));
	UFuncLib::CheckObject(this->_BuffClass, FSIG_APPEND(" this->_BuffClass is null"));
}

bool	URubyFlask::Activate(FEffectParameters& Parameters) {
	for (auto target : Parameters.Targets) {
		ABuffRubyFlask* buff = UFuncLib::SafeSpawnActor<ABuffRubyFlask>(Parameters.World, this->_BuffClass);
		if (UFuncLib::CheckObject(buff, "URubyFlask::Activate() buff failed to create ")) {
			buff->SetBaseDuration(10.0);
			//buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
			buff->AttachToActor(target->GetOwner(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
			buff->ApplyTo(target);
			/*
				TODO: pb: target is the PlayerState (see BP Arena)
					using a PlayerState as target is not possible for NPC...
					how do we manage HP or any statistics without PlayerState ?
					how do we replicate NPC state/attributes ?
			*/
		}
	}

	return Super::Activate(Parameters);
	//return this->UAbility::Activate(Parameters);
}
