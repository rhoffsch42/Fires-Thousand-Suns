
#include "AbilityBar.h"
#include "../FuncLib.h"

void	UAbilityBar::NativeConstruct() {
	Super::NativeConstruct();
}

void	UAbilityBar::LoadAbilityManager(UAbilityManager* Manager) {
	this->UI_Manager->LinkAbilityManager(Manager);
	this->UI_Picker->LinkAbilityManager(Manager);

	TArray<UWidget*> Children = this->UI_Manager->ContainerPanel->GetAllChildren();
	for (auto child : Children) {
		UAbilitySlot* slot = Cast<UAbilitySlot>(child);
		if (UFuncLib::CheckObject(slot, "UAbilityBar::LoadAbilityManager() Cast<UAbilitySlot> failed ")) {
			FScriptDelegate script;
			script.BindUFunction(this, "ManagerOnClick");
			slot->AbilitySlotClicked.Clear();
			slot->AbilitySlotClicked.Add(script);
		}
	}

	TArray<UWidget*> Children2 = this->UI_Picker->ContainerPanel->GetAllChildren();
	for (auto child : Children2) {
		UAbilitySlot* slot = Cast<UAbilitySlot>(child);
		if (UFuncLib::CheckObject(slot, "UAbilityBar::LoadAbilityManager() Cast<UAbilitySlot> failed ")) {
			FScriptDelegate script;
			script.BindUFunction(this, "PickerOnClick");
			slot->AbilitySlotClicked.Add(script);
		}
	}
}

void	UAbilityBar::ManagerOnClick(UAbilitySlot* InSlot) {
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString("UAbilityBar::ManagerOnClick()"));
	this->_LastSlotClicked = InSlot;
	this->UI_Picker->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void	UAbilityBar::PickerOnClick(UAbilitySlot* InSlot) {
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString("UAbilityBar::PickerOnClick()"));
	this->_LastSlotClicked->LinkAbility(InSlot->GetLinkedAbility());
	this->UI_Picker->SetVisibility(ESlateVisibility::Hidden);
}
