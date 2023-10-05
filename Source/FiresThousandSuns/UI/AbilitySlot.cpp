
#include "AbilitySlot.h"

void	UAbilitySlot::NativeConstruct() {
	this->bHasScriptImplementedTick = true;
	Super::NativeConstruct();

}

void	UAbilitySlot::Tick(FGeometry MyGeometry, float InDeltaTime) {
	Super::Tick(MyGeometry, InDeltaTime);

	if (this->_Ability) {
		this->UpdateWidget();
	}
}

void	UAbilitySlot::UpdateWidget() {
	this->CooldownSlider->SetValue(this->_Ability->Cooldown->RemainingRelative());
	this->Image->SetBrushFromMaterial(nullptr);//ability material
}

void	UAbilitySlot::LinkAbility(UAbility* Ability) {
	this->_Ability = Ability;
	this->UpdateWidget();
}

void	UAbilitySlot::UnLinkAbility() {
	this->_Ability = nullptr;
	this->CooldownSlider->SetValue(0.0f);
	this->Image->SetBrushFromMaterial(nullptr);
}
