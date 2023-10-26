#include "Ability.h"
#include "../Funclib.h"
#include "Kismet/GameplayStatics.h"

UAbility::UAbility() {
	FString name = FString::FormatAsNumber((int64)this);
	this->Cooldown = CreateDefaultSubobject<UCooldown>(*name); 
	if (UFuncLib::CheckObject(this->Cooldown, FString("UAbility() NewObject<UCooldown>() failed : "))) {
		this->Cooldown->World = this->GetWorld();
	}
	this->ActivationFailedSoundCue = LoadObject<USoundCue>(this->GetWorld(), *FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/mixkit-old-camera-shutter-click-1137_Cue.mixkit-old-camera-shutter-click-1137_Cue'"));
	
	UFuncLib::CheckObject(this->ActivationFailedSoundCue, "UAbilityFlameDash::UAbilitySteelskin() failed to LoadObject() USoundCue");
}

void	UAbility::TryActivate(FEffectParameters Parameters) {
	if (this->Cooldown->IsReady()) {
		this->Activate(Parameters);
	} else {
		UGameplayStatics::PlaySound2D(this->Cooldown->World, this->ActivationFailedSoundCue);
	}
}

bool	UAbility::Activate(FEffectParameters Parameters) {
	this->Cooldown->Use();
	UGameplayStatics::PlaySound2D(this->Cooldown->World, this->ActivationSuccessSoundCue);
	return true;
}

void	UAbility::SetNewMaterial(UObject* Outer, const FString MatPath) {
	this->IconMaterial = LoadObject<UMaterial>(Outer, *MatPath);
	UFuncLib::CheckObject(this->IconMaterial, FString("LoadObject<UMaterial>() failed : ").Append(MatPath));
}
