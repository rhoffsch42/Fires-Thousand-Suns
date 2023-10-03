// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayWidget.h"

void	UPlayWidget::NativeConstruct() {
	Super::NativeConstruct();

	this->InitSliders();
}

void	UPlayWidget::InitSliders() {
	this->NVSlider_MovSpeed->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_MovSpeed_Name",		"Bonus Movement Speed"),		0.0f, 100.0f);
	this->NVSlider_Life->SetTitleAndRange(				NSLOCTEXT("Fires", "NVSlider_Life_Name",			"Life"),						1.0f, 25000.0f);
	this->NVSlider_LifeRegen->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_LifeRegen_Name",		"Life Regeneration Rate"),		0.0f, 5000.0f);
	this->NVSlider_FireRes->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_FireRes_Name",			"Fire Resistance"),				0.0f, 90.0f);
	this->NVSlider_SpellSuppChance->SetTitleAndRange(	NSLOCTEXT("Fires", "NVSlider_SpellSuppChance_Name",	"Spell Suppression Chance"),	0.0f, 100.0f);
	this->NVSlider_SpellSuppEffect->SetTitleAndRange(	NSLOCTEXT("Fires", "NVSlider_SpellSuppEffect_Name",	"Spell SUppression Effect"),	40.0f, 90.0f);
	this->NVSlider_Fortify->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_Fortify_Name",			"Fortify Stacks"),				0.0f, 30.0f);
	this->NVSlider_LessDamage->SetTitleAndRange(		NSLOCTEXT("Fires", "NVSlider_LessDamage_Name",		"Less Damage"),					0.0f, 90.0f);

	this->NVSlider_MovSpeed->SetSliderValue(0.3f);
	this->NVSlider_Life->SetSliderValue(0.25f);
	this->NVSlider_LifeRegen->SetSliderValue(0.1f);
	this->NVSlider_FireRes->SetSliderValue(0.84f);
	this->NVSlider_SpellSuppChance->SetSliderValue(0.40f);
	this->NVSlider_SpellSuppEffect->SetSliderValue(0.2f);
	this->NVSlider_Fortify->SetSliderValue(0.0f);
	this->NVSlider_LessDamage->SetSliderValue(0.0f);
}


FPlayerStats	UPlayWidget::GeneratePlayerStats() const {
	return FPlayerStats{
		this->NVSlider_MovSpeed->GetValue() / 100.0,
		this->NVSlider_Life->GetValue(),
		this->NVSlider_LifeRegen->GetValue(),
		this->NVSlider_FireRes->GetValue() / 100,
		this->NVSlider_SpellSuppChance->GetValue() / 100,
		this->NVSlider_SpellSuppEffect->GetValue() / 100,
		this->NVSlider_Fortify->GetValue() / 100,
		this->NVSlider_LessDamage->GetValue() / 100,
	};
}
