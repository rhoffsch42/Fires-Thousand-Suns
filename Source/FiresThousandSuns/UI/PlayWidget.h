// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NamedValueSlider.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "../FiresThousandSunsPlayerState.h"
#include "Abilitys/AbilityManager.h"
#include "MenuContent.h"
#include "AbilitySlotManager.h"
#include "AbilityBar.h"

#include "PlayWidget.generated.h"

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UPlayWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void	InitSliders();
	UFUNCTION(BlueprintCallable)
	void	InitAbilitys();
	UFUNCTION(BlueprintCallable)
	void	InitFlasks();

	UFUNCTION(BlueprintCallable)
	void	ApplyPlayerStatistics(const FPlayerStatistics Stats);
	UFUNCTION(BlueprintCallable)
	void	ApplyDefaultArenaConfiguration();
	UFUNCTION(BlueprintCallable)
	FPlayerStatistics	GeneratePlayerStatistics() const;
	UFUNCTION(BlueprintCallable)
	void	LoadArenaConfigFromSaveGame(UPARAM(ref) UFiresThousandSunsSaveGame* SaveGame);


	UFUNCTION(BlueprintCallable)
	void	SaveArenaConfig(UPARAM(ref) UFiresThousandSunsSaveGame* SaveGame);
	UFUNCTION(BlueprintCallable)
	void	TransferArenaConfigToGameInstance();


	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UMenuContentButton* ButtonDefaultConfig;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_MovSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_Life;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_LifeRegen;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_FireRes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_SpellSuppChance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_SpellSuppEffect;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_Fortify;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCheckBox*	CheckBoxKrangledMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCheckBox*	CheckBoxUberMode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UAbilityBar* AbilityBar;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UAbilityBar* FlaskBar;

	UPROPERTY(BlueprintReadWrite)
	UAbilityManager* AbilityManager = nullptr;
	UPROPERTY(BlueprintReadWrite)
	UAbilityManager* FlaskManager = nullptr;
protected:
	virtual void NativeConstruct() override;
};
