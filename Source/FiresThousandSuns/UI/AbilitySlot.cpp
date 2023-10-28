
#include "AbilitySlot.h"
#include "../FuncLib.h"

void	UAbilitySlot::NativeConstruct() {
	Super::NativeConstruct();
	this->bHasScriptImplementedTick = true;
	this->_FormatOptions.MaximumFractionalDigits = 0;
	this->UseCountText->SetVisibility(ESlateVisibility::Hidden);
	this->KeyBindText->SetVisibility(ESlateVisibility::Hidden);

	FScriptDelegate	script;
	script.BindUFunction(this, "OnSlotClicked");
	this->Button->OnClicked.Add(script);
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString("UAbilitySlot::NativeConstruct() bind 0"));
}

void	UAbilitySlot::NativeTick(const FGeometry & MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

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
			this->UseCountText->SetText(FText::AsNumber(this->_Ability->Cooldown->GetAvailableUses(), &this->_FormatOptions));
		}
	}
}

// If Ability is null, this will not cancel the link and let the slot as is, it will concider it as an unlink() and reset the slot !
void	UAbilitySlot::LinkAbility(UAbility* Ability) {
	this->_Ability = Ability;

	if (!this->_Ability) {
		this->UnLinkAbility();
	} else {
		if (this->_Ability->IconMaterial) {
			if (this->Image) {
				this->Image->SetBrushFromMaterial(this->_Ability->IconMaterial);
				this->Image->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
		this->SetToolTipText(FText::FromString(this->_Ability->TooltipName));
		// this has to be done elsewhere if user changes the max uses
		this->UseCountText->SetVisibility(
			(this->_Ability->Cooldown->GetMaxUses() > 1) ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
	
	}

	this->UpdateWidget();
}

void	UAbilitySlot::UnLinkAbility() {
	this->_Ability = nullptr;
	this->CooldownBar->SetPercent(0.0f);
	this->Image->SetBrushFromMaterial(nullptr);
	this->Image->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
	this->UseCountText->SetVisibility(ESlateVisibility::Hidden);
	this->SetToolTipText(FText());
}

// Returns true if we found a key bind in the InputMappingContext for the InputAction. 
bool	UAbilitySlot::LinkInputAction(UPARAM(ref) UInputMappingContext* InputMappingContext, UPARAM(ref) UInputAction* InputAction) {
	if (!UFuncLib::CheckObject(InputMappingContext, "UAbilitySlot::LinkInputAction() InputMappingContext is null.")) {
		return false;
	}
	this->_InputAction = InputAction;

	bool	bFoundBinding = false;
	if (this->_InputAction) {
		TArray<FEnhancedActionKeyMapping> mapping = InputMappingContext->GetMappings();
		for (auto element : mapping) {
			if (element.Action == InputAction) {
				this->KeyBindText->SetText(element.Key.GetDisplayName());
				this->KeyBindText->SetVisibility(ESlateVisibility::HitTestInvisible);
				bFoundBinding = true;
				//this->UpdateWidget(); // no need ?
				break;//we take the first binding
			}
		}
	}
	if (!this->_InputAction) {//should not be possible with a ref ?
		this->UnLinkInputAction();
	}

	return bFoundBinding;
}

void	UAbilitySlot::UnLinkInputAction() {
	this->_InputAction = nullptr;
	this->KeyBindText->SetVisibility(ESlateVisibility::Hidden);
}


void	UAbilitySlot::OnSlotClicked() {
	//GEngine->AddOnScreenDebugMessage((int32)(int64)this, 5.0f, FColor::Purple, FString::Printf(
	//	TEXT("UAbilitySlot::OnSlotClicked() %p"),
	//	this->_Ability
	//));
	this->AbilitySlotClicked.Broadcast(this);
}

UAbility* UAbilitySlot::GetLinkedAbility() const { return this->_Ability; }
