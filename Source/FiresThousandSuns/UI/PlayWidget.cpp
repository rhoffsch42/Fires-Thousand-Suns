#include "PlayWidget.h"
#include "../Abilitys/AbilityFlameDash.h"
#include "../Abilitys/AbilityMoltenShell.h"
#include "../FuncLib.h"

void	UPlayWidget::NativeConstruct() {
	Super::NativeConstruct();

	this->InitSliders();
	this->InitAbilitys();
}

void	UPlayWidget::InitSliders() {
	this->NVSlider_MovSpeed->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_MovSpeed_Name",		"Bonus Movement Speed"),		0.0f, 100.0f);
	this->NVSlider_Life->SetTitleAndRange(				NSLOCTEXT("Fires", "NVSlider_Life_Name",			"Life"),						1.0f, 25000.0f);
	this->NVSlider_LifeRegen->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_LifeRegen_Name",		"Life Regeneration Rate"),		0.0f, 5000.0f);
	this->NVSlider_FireRes->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_FireRes_Name",			"Fire Resistance"),				0.0f, 90.0f);
	this->NVSlider_SpellSuppChance->SetTitleAndRange(	NSLOCTEXT("Fires", "NVSlider_SpellSuppChance_Name",	"Spell Suppression Chance"),	0.0f, 100.0f);
	this->NVSlider_SpellSuppEffect->SetTitleAndRange(	NSLOCTEXT("Fires", "NVSlider_SpellSuppEffect_Name",	"Spell Suppression Effect"),	40.0f, 90.0f);
	this->NVSlider_Fortify->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_Fortify_Name",			"Fortify Stacks"),				0.0f, 30.0f);
	this->NVSlider_LessDamage->SetTitleAndRange(		NSLOCTEXT("Fires", "NVSlider_LessDamage_Name",		"Less Damage"),					0.0f, 90.0f);

	this->NVSlider_MovSpeed->SetSliderValue(0.4f);
	this->NVSlider_Life->SetSliderValue(0.25f);
	this->NVSlider_LifeRegen->SetSliderValue(0.05f);
	this->NVSlider_FireRes->SetSliderValue(0.84f);
	this->NVSlider_SpellSuppChance->SetSliderValue(1.0f);
	this->NVSlider_SpellSuppEffect->SetSliderValue(0.2f);
	this->NVSlider_Fortify->SetSliderValue(0.0f);
	this->NVSlider_LessDamage->SetSliderValue(0.0f);
}

static inline void	ClearAbilitySlot(UWidget* Slot) {
	UAbilitySlot* AbSlot = Cast<UAbilitySlot>(Slot);
	if (UFuncLib::CheckObject(AbSlot, "UPlayWidget ClearAbilitySlot() cast failed : UAbilitySlot")) {
		AbSlot->UnLinkAbility();
	}
}

void	UPlayWidget::InitAbilitys() {
	// Abilitys
	UAbilityFlameDash* FlameDash = NewObject<UAbilityFlameDash>();
	FlameDash->Cooldown->World = this->GetWorld();

	UAbilityMoltenShell* MoltenShell = NewObject<UAbilityMoltenShell>();
	MoltenShell->Cooldown->World = this->GetWorld();

	UAbilityMoltenShell* VaalMoltenShell = NewObject<UAbilityMoltenShell>();
	//VaalMoltenShell->ShellHP = 10000.0;
	//VaalMoltenShell->ShellDuration = 10.8;
	//VaalMoltenShell->ShellAbsorbtion = 0.39;
	VaalMoltenShell->Cooldown->World = this->GetWorld();
	//VaalMoltenShell->Cooldown->SetDuration(50.0);
	VaalMoltenShell->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/FireShield_red_01_50x50_UIMat.FireShield_red_01_50x50_UIMat'"));

	UAbilityMoltenShell* Steelskin = NewObject<UAbilityMoltenShell>();
	//Steelskin->ShellHP = 2209;
	//Steelskin->ShellDuration = 1.5;
	//Steelskin->ShellAbsorbtion = 0.70;
	Steelskin->Cooldown->World = this->GetWorld();
	//Steelskin->Cooldown->SetDuration(4.05);
	Steelskin->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/aura_100x100_UIMat.aura_100x100_UIMat'"));

	this->AbilityManager = NewObject<UAbilityManager>();
	this->AbilityManager->SetAbilityAmount(5);
	this->AbilityManager->SetAbility(0, nullptr); // shieldCharge // /Script/Engine.Material'/Game/LevelPrototyping/Materials/shield-bash_100x100_UIMat.shield-bash_100x100_UIMat'
	this->AbilityManager->SetAbility(1, FlameDash);
	this->AbilityManager->SetAbility(2, Steelskin);
	this->AbilityManager->SetAbility(3, MoltenShell);
	this->AbilityManager->SetAbility(4, VaalMoltenShell);

	UFuncLib::CheckObject(FlameDash->Cooldown->World, "PlayWidget : Missing Cooldown->World on _FlameDash");
	UFuncLib::CheckObject(Steelskin->Cooldown->World, "PlayWidget : Missing Cooldown->World on _Steelskin");
	UFuncLib::CheckObject(MoltenShell->Cooldown->World, "PlayWidget : Missing Cooldown->World on _MoltenShell");
	UFuncLib::CheckObject(VaalMoltenShell->Cooldown->World, "PlayWidget : Missing Cooldown->World on _VaalMoltenShell");

	this->UI_AbilityManager->LinkAbilityManager(this->AbilityManager);
	ClearAbilitySlot(this->UI_AbilityManager->ContainerPanel->GetChildAt(0));
	ClearAbilitySlot(this->UI_AbilityManager->ContainerPanel->GetChildAt(2));
	ClearAbilitySlot(this->UI_AbilityManager->ContainerPanel->GetChildAt(4));
	this->UI_AbilityManager_Picker->LinkAbilityManager(this->AbilityManager);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString("UPlayWidget::InitAbilitys() done."));
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
