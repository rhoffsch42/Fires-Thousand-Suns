#include "PlayWidget.h"
#include "../Abilitys/AbilityFlameDash.h"
#include "../Abilitys/AbilityMoltenShell.h"
#include "../Abilitys/LifeFlask.h"
//#include "../Abilitys/RubyFlask.h"
#include "../FiresThousandSunsSaveGame.h"
#include "../FuncLib.h"

void	UPlayWidget::NativeConstruct() {
	Super::NativeConstruct();

	this->InitSliders();
	this->InitAbilitys();
	this->InitFlasks();
	this->CheckBoxUberMode->SetIsChecked(true);

	FScriptDelegate script;
	script.BindUFunction(this, "ApplyDefaultArenaConfiguration");
	this->ButtonDefaultConfig->Button->OnClicked.Add(script);
	this->ButtonDefaultConfig->ButtonText->SetText(FText::FromString("Default values"));
}

void	UPlayWidget::InitSliders() {
	this->NVSlider_MovSpeed->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_MovSpeed_Name",		"Bonus Movement Speed"),		0.0f, 100.0f);
	this->NVSlider_Life->SetTitleAndRange(				NSLOCTEXT("Fires", "NVSlider_Life_Name",			"Life"),						1.0f, 10000.0f);
	this->NVSlider_LifeRegen->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_LifeRegen_Name",		"Life Regeneration Rate"),		0.0f, 1000.0f);
	this->NVSlider_FireRes->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_FireRes_Name",			"Fire Resistance"),				0.0f, 90.0f);
	this->NVSlider_SpellSuppChance->SetTitleAndRange(	NSLOCTEXT("Fires", "NVSlider_SpellSuppChance_Name",	"Spell Suppression Chance"),	0.0f, 100.0f);
	this->NVSlider_SpellSuppEffect->SetTitleAndRange(	NSLOCTEXT("Fires", "NVSlider_SpellSuppEffect_Name",	"Spell Suppression Effect"),	40.0f, 60.0f);
	this->NVSlider_Fortify->SetTitleAndRange(			NSLOCTEXT("Fires", "NVSlider_Fortify_Name",			"Fortify Stacks"),				0.0f, 20.0f);

	this->ApplyDefaultArenaConfiguration();
}

static inline void	ClearAbilitySlot(UWidget* Slot) {
	UAbilitySlot* AbSlot = Cast<UAbilitySlot>(Slot);
	if (UFuncLib::CheckObject(AbSlot, "UPlayWidget ClearAbilitySlot() cast failed : UAbilitySlot")) {
		AbSlot->UnLinkAbility();
	}
}

void	UPlayWidget::InitAbilitys() {
	UAbilityFlameDash* FlameDash = NewObject<UAbilityFlameDash>(this, GEN_UNAME(this));
	UAbilityMoltenShell* MoltenShell = NewObject<UAbilityMoltenShell>(this, GEN_UNAME(this));
	UAbilityVaalMoltenShell* VaalMoltenShell = NewObject<UAbilityVaalMoltenShell>(this, GEN_UNAME(this));
	UAbilitySteelskin* Steelskin = NewObject<UAbilitySteelskin>(this, GEN_UNAME(this));

	this->AbilityManager = NewObject<UAbilityManager>(this, GEN_UNAME(this));
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
}

void	UPlayWidget::InitFlasks() {
	ULifeFlask* LifeFlask = NewObject<ULifeFlask>(this, GEN_UNAME(this));
	URubyFlask* RubyFlask = NewObject<URubyFlask>(this, GEN_UNAME(this));

	this->FlaskManager = NewObject<UAbilityManager>(this, GEN_UNAME(this));
	this->FlaskManager->SetAbilityAmount(5);
	this->FlaskManager->SetAbility(0, nullptr);
	this->FlaskManager->SetAbility(1, LifeFlask);
	this->FlaskManager->SetAbility(2, RubyFlask);
	this->FlaskManager->SetAbility(3, nullptr);
	this->FlaskManager->SetAbility(4, nullptr);

	UFuncLib::CheckObject(LifeFlask->Cooldown->World, "PlayWidget : Missing Cooldown->World on LifeFlask");
	UFuncLib::CheckObject(RubyFlask->Cooldown->World, "PlayWidget : Missing Cooldown->World on RubyFlask");

	this->FlaskBar->LoadAbilityManager(this->FlaskManager);
}

void	UPlayWidget::ApplyPlayerStatistics(const FPlayerStatistics Stats) {
	this->NVSlider_MovSpeed->UpdateWithValue(Stats.MovementSpeed);
	this->NVSlider_Life->UpdateWithValue(Stats.Life);
	this->NVSlider_LifeRegen->UpdateWithValue(Stats.LifeRegeneration);
	this->NVSlider_FireRes->UpdateWithValue(Stats.FireResistance);
	this->NVSlider_SpellSuppChance->UpdateWithValue(Stats.SpellSuppressionChance);
	this->NVSlider_SpellSuppEffect->UpdateWithValue(Stats.SpellSuppressionEffect);
	this->NVSlider_Fortify->UpdateWithValue(Stats.FortifyEffect);
}

void	UPlayWidget::ApplyDefaultArenaConfiguration() {
	this->ApplyPlayerStatistics(FPlayerStatistics());
}

FPlayerStatistics	UPlayWidget::GeneratePlayerStatistics() const {
	return FPlayerStatistics{
		(int32)this->NVSlider_MovSpeed->GetValue(),
		(int32)this->NVSlider_Life->GetValue(),
		(int32)this->NVSlider_LifeRegen->GetValue(),
		(int32)this->NVSlider_FireRes->GetValue(),
		(int32)this->NVSlider_SpellSuppChance->GetValue(),
		(int32)this->NVSlider_SpellSuppEffect->GetValue(),
		(int32)this->NVSlider_Fortify->GetValue(),
	};
}

void	UPlayWidget::LoadArenaConfigFromSaveGame(UPARAM(ref) UFiresThousandSunsSaveGame* SaveGame) {
	if (UFuncLib::CheckObject(SaveGame, FString(__func__).Append(" SaveGame is null"))) {
		this->ApplyPlayerStatistics(SaveGame->PlayerStatistics);
		this->AbilityBar->UI_Manager->SetLayout(SaveGame->AbilityLayout);
		this->FlaskBar->UI_Manager->SetLayout(SaveGame->FlaskLayout, true);
	}
}


void	UPlayWidget::SaveArenaConfig(UPARAM(ref) UFiresThousandSunsSaveGame* SaveGame) {
	if (UFuncLib::CheckObject(SaveGame, FString(__func__).Append(" SaveGame is null"))) {
		SaveGame->PlayerStatistics = this->GeneratePlayerStatistics();
		SaveGame->AbilityLayout = this->AbilityBar->UI_Manager->GetLayoutAsAbilityType();
		SaveGame->FlaskLayout = this->FlaskBar->UI_Manager->GetLayoutAsAbilityType();
		SaveGame->Save();
	}
}

// repetitive with SaveArenaConfig. Use SaveGame for all shared values and only transfer unsaved values ?
void	UPlayWidget::TransferArenaConfigToGameInstance() {
	UFiresThousandSunsGameInstance* Fires_GI = Cast<UFiresThousandSunsGameInstance>(this->GetGameInstance());
	if (UFuncLib::CheckObject(Fires_GI, FString(__func__).Append(" Game instance is null or cast failed "))) {
		// shared with SaveGame
		Fires_GI->BaseStats = this->GeneratePlayerStatistics();
		Fires_GI->AbilityLayout = this->AbilityBar->UI_Manager->GetLayoutAsAbilityType();
		Fires_GI->FlaskLayout = this->FlaskBar->UI_Manager->GetLayoutAsAbilityType();
		// not saved, thus not shared
		Fires_GI->bUberMode = this->CheckBoxUberMode->IsChecked();
		Fires_GI->bKrangledWaves = this->CheckBoxKrangledMode->IsChecked();
	}
}
