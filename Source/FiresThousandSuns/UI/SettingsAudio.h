// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"

#include "SettingsAudio.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API USettingsAudio : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void	SetDefaultVolumes();

	UFUNCTION(BlueprintCallable)
	void	LinkMasterVolumeSoundClass(USoundClass* Sound);
	UFUNCTION(BlueprintCallable)
	void	LinkEffectsVolumeSoundClass(USoundClass* Sound);
	UFUNCTION(BlueprintCallable)
	void	LinkMusicVolumeSoundClass(USoundClass* Sound);
	UFUNCTION(BlueprintCallable)
	void	LinkDialoguesVolumeSoundClass(USoundClass* Sound);
	UFUNCTION(BlueprintCallable)
	void	LinkAmbientVolumeSoundClass(USoundClass* Sound);


	UFUNCTION(BlueprintCallable)
	void	SetMasterVolume(float Value) const;
	UFUNCTION(BlueprintCallable)
	void	SetEffectsVolume(float Value) const;
	UFUNCTION(BlueprintCallable)
	void	SetMusicVolume(float Value) const;
	UFUNCTION(BlueprintCallable)
	void	SetDialoguesVolume(float Value) const;
	UFUNCTION(BlueprintCallable)
	void	SetAmbientVolume(float Value) const;

	UFUNCTION(BlueprintCallable)
	void	UpdateMasterVolume(float Value) const;
	UFUNCTION(BlueprintCallable)
	void	UpdateEffectsVolume(float Value) const;
	UFUNCTION(BlueprintCallable)
	void	UpdateMusicVolume(float Value) const;
	UFUNCTION(BlueprintCallable)
	void	UpdateDialoguesVolume(float Value) const;
	UFUNCTION(BlueprintCallable)
	void	UpdateAmbientVolume(float Value) const;

	UFUNCTION(BlueprintCallable)
	float	GetMasterVolumeValue() const;
	UFUNCTION(BlueprintCallable)
	float	GetEffectsVolumeValue() const;
	UFUNCTION(BlueprintCallable)
	float	GetMusicVolumeValue() const;
	UFUNCTION(BlueprintCallable)
	float	GetDialoguesVolumeValue() const;
	UFUNCTION(BlueprintCallable)
	float	GetAmbientVolumeValue() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundMix* SoundMix = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	USlider* MasterVolumeSlider;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	USlider* EffectsVolumeSlider;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	USlider* MusicVolumeSlider;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	USlider* DialoguesVolumeSlider;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	USlider* AmbientVolumeSlider;
protected:
	virtual void NativeConstruct() override;
	void	_LinkSliderToFunc(USlider* Slider, const FName& FuncName);
	USoundClass* _MasterSound = nullptr;
	USoundClass* _EffectsSound = nullptr;
	USoundClass* _MusicSound = nullptr;
	USoundClass* _DialoguesSound = nullptr;
	USoundClass* _AmbientSound = nullptr;
};
