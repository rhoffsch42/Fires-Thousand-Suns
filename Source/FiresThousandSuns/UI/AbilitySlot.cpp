
#include "AbilitySlot.h"

void	UAbilitySlot::NativeConstruct() {
	this->bHasScriptImplementedTick = true;
	Super::NativeConstruct();

	FScriptDelegate	script;
	script.BindUFunction(this, "OnSlotClicked");
	this->AbilitySlotClicked.Add(script);
}

void	UAbilitySlot::Tick(FGeometry MyGeometry, float InDeltaTime) {
	Super::Tick(MyGeometry, InDeltaTime);

	this->UpdateWidget();
}

void	UAbilitySlot::UpdateWidget() {
	if (this->_Ability) {
		this->CooldownBar->SetPercent(this->_Ability->Cooldown->RemainingRelative());
	}
}

void	UAbilitySlot::LinkAbility(UAbility* Ability) {
	this->_Ability = Ability;
	if (Ability->IconMaterial) {
		//UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(Ability->IconMaterial->GetMaterialInterface(), Ability->IconMaterial->GetMaterialInterface());
		if (this->Image) { this->Image->SetBrushFromMaterial(Ability->IconMaterial); }
	}
	this->UpdateWidget();
}

void	UAbilitySlot::UnLinkAbility() {
	this->_Ability = nullptr;
	this->CooldownBar->SetPercent(0.0f);
	this->Image->SetBrushFromMaterial(nullptr);
}

void	UAbilitySlot::OnSlotClicked() {
	this->AbilitySlotClicked.Broadcast(this);
}
