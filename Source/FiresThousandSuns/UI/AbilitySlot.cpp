
#include "AbilitySlot.h"
#include "../FuncLib.h"

void	UAbilitySlot::NativeConstruct() {
	this->bHasScriptImplementedTick = true;
	Super::NativeConstruct();

	FScriptDelegate	script;
	script.BindUFunction(this, "OnSlotClicked");
	this->Button->OnClicked.Add(script);
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString("UAbilitySlot::NativeConstruct() bind 0"));
}

void	UAbilitySlot::NativeTick(const FGeometry & MyGeometry, float InDeltaTime) {
	Super::Tick(MyGeometry, InDeltaTime);

	this->UpdateWidget();
}

void	UAbilitySlot::UpdateWidget() {
	if (this->_Ability) {
		//GEngine->AddOnScreenDebugMessage((int32)(int64)this, 5.0f, FColor::Yellow, FString::Printf(
		//	TEXT("UAbilitySlot::UpdateWidget() %d / %d | %f"),
		//	this->_Ability->Cooldown->GetAvailableUses(),
		//	this->_Ability->Cooldown->GetMaxUses(),
		//	this->_Ability->Cooldown->Remaining()
		//));
		if (UFuncLib::CheckObject(this->_Ability->Cooldown, "UAbilitySlot::UpdateWidget() _Ability->Cooldown is nullptr")) {
			this->CooldownBar->SetPercent(this->_Ability->Cooldown->RemainingRelative());
		}
	}
}

void	UAbilitySlot::LinkAbility(UAbility* Ability) {
	this->_Ability = Ability;
	if (this->_Ability) {
		if (this->_Ability->IconMaterial) {
			//UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(Ability->IconMaterial->GetMaterialInterface(), Ability->IconMaterial->GetMaterialInterface());
			if (this->Image) {
				this->Image->SetBrushFromMaterial(this->_Ability->IconMaterial);
				this->Image->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	} else {
		this->Image->SetBrushFromMaterial(nullptr);
		this->Image->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
	}
	this->UpdateWidget();
}

void	UAbilitySlot::UnLinkAbility() {
	this->_Ability = nullptr;
	this->CooldownBar->SetPercent(0.0f);
	this->Image->SetBrushFromMaterial(nullptr);
	this->Image->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
}

void	UAbilitySlot::OnSlotClicked() {
	GEngine->AddOnScreenDebugMessage((int32)(int64)this, 5.0f, FColor::Purple, FString::Printf(
		TEXT("UAbilitySlot::OnSlotClicked() %p"),
		this->_Ability
	));
	this->AbilitySlotClicked.Broadcast(this);
}

UAbility* UAbilitySlot::GetLinkedAbility() const { return this->_Ability; }