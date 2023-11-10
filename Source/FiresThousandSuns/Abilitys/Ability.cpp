#include "Ability.h"
#include "../Funclib.h"
#include "Kismet/GameplayStatics.h"
#include "../FiresThousandSunsPlayerController.h"

UAbility::UAbility() {
	this->Cooldown = CreateDefaultSubobject<UCooldown>(GEN_UNAME(this));
	this->CastTime = CreateDefaultSubobject<UCooldown>(GEN_UNAME(this));
	this->ActivationFailedSoundCue = LoadObject<USoundCue>(this->GetWorld(), *FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/mixkit-old-camera-shutter-click-1137_Cue.mixkit-old-camera-shutter-click-1137_Cue'"));
}

void	UAbility::PostInitProperties() {
	Super::PostInitProperties();

	if (UFuncLib::CheckObject(this->Cooldown, FString("UAbility() NewObject<UCooldown>() failed : "))) {
		this->Cooldown->World = this->GetWorld();
	}
	if (UFuncLib::CheckObject(this->Cooldown, FString("UAbility() NewObject<UCooldown>() failed : "))) {
		this->CastTime->World = this->GetWorld();
	}

	UFuncLib::CheckObject(this->ActivationFailedSoundCue, "UAbility() failed to LoadObject() USoundCue");
	UFuncLib::CheckObject(this->Cooldown->World, "UAbility() Cooldown->World null");
	UFuncLib::CheckObject(this->CastTime->World, "UAbility() CastTime->World null");
}

bool	UAbility::TryActivate(FEffectParameters Parameters) {
	if (this->Cooldown->IsReady() && this->IsActivatable(Parameters)) {
		return (this->bIsInstant ? this->Activate(Parameters) : this->StartCasting(Parameters));
	} else {
		UGameplayStatics::PlaySound2D(this->Cooldown->World, this->ActivationFailedSoundCue);
		return false;
	}
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
		return playerCtrl->SetCastedAbility(this, Parameters);
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
