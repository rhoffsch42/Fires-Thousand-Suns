#include "Ability.h"
#include "../Funclib.h"
#include "Kismet/GameplayStatics.h"
#include "../FiresThousandSunsPlayerController.h"

UAbility::UAbility() {
	this->Cooldown = CreateDefaultSubobject<UCooldown>(GEN_UNAME(this));
	if (UFuncLib::CheckObject(this->Cooldown, FString("UAbility() NewObject<UCooldown>() failed : "))) {
		this->Cooldown->World = this->GetWorld();
	}
	this->CastTime = CreateDefaultSubobject<UCooldown>(GEN_UNAME(this));
	if (UFuncLib::CheckObject(this->Cooldown, FString("UAbility() NewObject<UCooldown>() failed : "))) {
		this->CastTime->World = this->GetWorld();
	}
	this->ActivationFailedSoundCue = LoadObject<USoundCue>(this->GetWorld(), *FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/mixkit-old-camera-shutter-click-1137_Cue.mixkit-old-camera-shutter-click-1137_Cue'"));
	
	UFuncLib::CheckObject(this->ActivationFailedSoundCue, "UAbilityFlameDash::UAbilitySteelskin() failed to LoadObject() USoundCue");
}

bool	UAbility::TryActivate(FEffectParameters Parameters) {
	if (this->Cooldown->IsReady() && this->IsActivatable(Parameters)) {
		if (this->bIsInstant) {
			return this->Activate(Parameters);
		} else {
			return this->StartCasting(Parameters);
		}
	} else {
		UGameplayStatics::PlaySound2D(this->Cooldown->World, this->ActivationFailedSoundCue);
	}
	return false;
}

bool	UAbility::IsActivatable(FEffectParameters Parameters) {
	return true;
}

bool	UAbility::StartCasting(FEffectParameters Parameters) {
	if (this->CastTime->IsReady()) {
		return this->Activate(Parameters);
	} else {
		UPlayer* owner = Parameters.ActorInstigator->GetNetOwningPlayer();
		AFiresThousandSunsPlayerController* playerCtrl = Cast<AFiresThousandSunsPlayerController>(owner->GetPlayerController(0));
		if (!UFuncLib::CheckObject(playerCtrl, "[AbilityFlameDash] PlayerController is null or cast failed.")) {
			return false;
		}
		playerCtrl->SetCastedAbility(this, Parameters);
		return true;
	}
}

bool	UAbility::Activate(FEffectParameters Parameters, bool CheckActivatable) {
	this->Cooldown->Use();
	this->CastTime->Use();
	UGameplayStatics::PlaySound2D(this->Cooldown->World, this->ActivationSuccessSoundCue);
	return true;
}

void	UAbility::SetNewMaterial(UObject* Outer, const FString MatPath) {
	this->IconMaterial = LoadObject<UMaterial>(Outer, *MatPath);
	UFuncLib::CheckObject(this->IconMaterial, FString("LoadObject<UMaterial>() failed : ").Append(MatPath));
}
