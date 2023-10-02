
#include "SettingsAudio.h"
#include "Kismet/GameplayStatics.h"


void	USettingsAudio::NativeConstruct() {
	Super::NativeConstruct();
}

void	USettingsAudio::_LinkSliderToFunc(USlider* Slider, const FName& FuncName) {
	Slider->OnValueChanged.Clear();
	FScriptDelegate script;
	script.BindUFunction(this, FuncName);
	Slider->OnValueChanged.Add(script);
}

void	USettingsAudio::LinkMasterVolumeSoundClass(USoundClass* Sound) {
	this->_MasterSound = Sound;
	this->_LinkSliderToFunc(this->MasterVolumeSlider, "UpdateMasterVolume");
}

void	USettingsAudio::LinkEffectsVolumeSoundClass(USoundClass* Sound) {
	this->_EffectsSound = Sound;
	this->_LinkSliderToFunc(this->EffectsVolumeSlider, "UpdateEffectsVolume");
}

void	USettingsAudio::LinkMusicVolumeSoundClass(USoundClass* Sound) {
	this->_MusicSound = Sound;
	this->_LinkSliderToFunc(this->MusicVolumeSlider, "UpdateMusicVolume");
}

void	USettingsAudio::LinkDialoguesVolumeSoundClass(USoundClass* Sound) {
	this->_DialoguesSound = Sound;
	this->_LinkSliderToFunc(this->DialoguesVolumeSlider, "UpdateDialoguesVolume");
}

void	USettingsAudio::UpdateMasterVolume(float Value) const {
	if (this->SoundMix->IsValidLowLevel() && this->_MasterSound->IsValidLowLevel()) {
		UGameplayStatics::SetSoundMixClassOverride(this->GetWorld(), this->SoundMix, this->_MasterSound, Value, 1.0, 0.0);
	}
}

void	USettingsAudio::UpdateEffectsVolume(float Value) const {
	if (this->SoundMix->IsValidLowLevel() && this->_EffectsSound->IsValidLowLevel()) {
		UGameplayStatics::SetSoundMixClassOverride(this->GetWorld(), this->SoundMix, this->_EffectsSound, Value, 1.0, 0.0);
	}
}

void	USettingsAudio::UpdateMusicVolume(float Value) const {
	if (this->SoundMix->IsValidLowLevel() && this->_MusicSound->IsValidLowLevel()) {
		UGameplayStatics::SetSoundMixClassOverride(this->GetWorld(), this->SoundMix, this->_MusicSound, Value, 1.0, 0.0);
	}
}

void	USettingsAudio::UpdateDialoguesVolume(float Value) const {
	if (this->SoundMix->IsValidLowLevel() && this->_DialoguesSound->IsValidLowLevel()) {
		UGameplayStatics::SetSoundMixClassOverride(this->GetWorld(), this->SoundMix, this->_DialoguesSound, Value, 1.0, 0.0);
	}
}

void	USettingsAudio::SetMasterVolume(float Value) const {
	this->MasterVolumeSlider->SetValue(Value);
	this->UpdateMasterVolume(Value);
}
void	USettingsAudio::SetEffectsVolume(float Value) const {
	this->EffectsVolumeSlider->SetValue(Value);
	this->UpdateEffectsVolume(Value);
}
void	USettingsAudio::SetMusicVolume(float Value) const {
	this->MusicVolumeSlider->SetValue(Value);
	this->UpdateMusicVolume(Value);
}
void	USettingsAudio::SetDialoguesVolume(float Value) const {
	this->DialoguesVolumeSlider->SetValue(Value);
	this->UpdateDialoguesVolume(Value);
}
