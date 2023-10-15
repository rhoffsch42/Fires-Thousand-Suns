#include "PlayWidget.h"
#include "../Abilitys/AbilityFlameDash.h"
#include "../Abilitys/AbilityMoltenShell.h"
#include "../Abilitys/LifeFlask.h"
//#include "../Abilitys/RubyFlask.h"
#include "../FuncLib.h"

void	UPlayWidget::NativeConstruct() {
	Super::NativeConstruct();

	this->InitSliders();
	this->InitAbilitys();
	this->InitFlasks();
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
	UAbilityFlameDash* FlameDash = NewObject<UAbilityFlameDash>();
	UAbilityMoltenShell* MoltenShell = NewObject<UAbilityMoltenShell>();
	UAbilityVaalMoltenShell* VaalMoltenShell = NewObject<UAbilityVaalMoltenShell>();
	UAbilitySteelskin* Steelskin = NewObject<UAbilitySteelskin>();
	FlameDash->Cooldown->World = this->GetWorld();
	MoltenShell->Cooldown->World = this->GetWorld();
	VaalMoltenShell->Cooldown->World = this->GetWorld();
	Steelskin->Cooldown->World = this->GetWorld();

	this->AbilityManager = NewObject<UAbilityManager>();
	this->AbilityManager->SetAbilityAmount(5);
	this->AbilityManager->SetAbility(0, nullptr); // used as a 'slot clearer'
	this->AbilityManager->SetAbility(1, FlameDash);
	this->AbilityManager->SetAbility(2, Steelskin);
	this->AbilityManager->SetAbility(3, MoltenShell);
	this->AbilityManager->SetAbility(4, VaalMoltenShell);
	// shieldCharge // /Script/Engine.Material'/Game/LevelPrototyping/Materials/shield-bash_100x100_UIMat.shield-bash_100x100_UIMat'

	UFuncLib::CheckObject(FlameDash->Cooldown->World, "PlayWidget : Missing Cooldown->World on _FlameDash");
	UFuncLib::CheckObject(Steelskin->Cooldown->World, "PlayWidget : Missing Cooldown->World on _Steelskin");
	UFuncLib::CheckObject(MoltenShell->Cooldown->World, "PlayWidget : Missing Cooldown->World on _MoltenShell");
	UFuncLib::CheckObject(VaalMoltenShell->Cooldown->World, "PlayWidget : Missing Cooldown->World on _VaalMoltenShell");

	this->AbilityBar->LoadAbilityManager(this->AbilityManager);
	ClearAbilitySlot(this->AbilityBar->UI_Manager->ContainerPanel->GetChildAt(0));
	ClearAbilitySlot(this->AbilityBar->UI_Manager->ContainerPanel->GetChildAt(2));
	ClearAbilitySlot(this->AbilityBar->UI_Manager->ContainerPanel->GetChildAt(4));

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString("UPlayWidget::InitAbilitys() done."));
}

void	UPlayWidget::InitFlasks() {
	ULifeFlask* LifeFlask = NewObject<ULifeFlask>();
	URubyFlask* RubyFlask = NewObject<URubyFlask>();
	LifeFlask->Cooldown->World = this->GetWorld();
	RubyFlask->Cooldown->World = this->GetWorld();

	this->FlaskManager = NewObject<UAbilityManager>();
	this->FlaskManager->SetAbilityAmount(5);
	this->FlaskManager->SetAbility(0, nullptr);
	this->FlaskManager->SetAbility(1, LifeFlask);
	this->FlaskManager->SetAbility(2, RubyFlask);
	this->FlaskManager->SetAbility(3, nullptr);
	this->FlaskManager->SetAbility(4, nullptr);

	UFuncLib::CheckObject(LifeFlask->Cooldown->World, "PlayWidget : Missing Cooldown->World on LifeFlask");
	UFuncLib::CheckObject(RubyFlask->Cooldown->World, "PlayWidget : Missing Cooldown->World on RubyFlask");

	this->FlaskBar->LoadAbilityManager(this->FlaskManager);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString("UPlayWidget::InitFlasks() done."));
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
