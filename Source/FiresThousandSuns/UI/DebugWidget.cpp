#include "DebugWidget.h"
#include "../FuncLib.h"

void	UDebugLine::NativeConstruct() {
	Super::NativeConstruct();
}
void	UDebugLine::NativeOnInitialized() {
	Super::NativeOnInitialized();
}
void	UDebugLine::SetMessage(FString Message) {
	this->TextBox->SetText(FText::FromString(Message));
}
///////////////////////////////

void	UDebugWidget::NativeConstruct() {
	Super::NativeConstruct();
}
void	UDebugWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();
}

void	UDebugWidget::AddMessage(FString Message) {
	UDebugLine* Line = CreateWidget<UDebugLine>(this, this->LineWidgetClass);
	if (UFuncLib::CheckObject(Line, FSIG_APPEND(" Line creation failed"))) {
		Line->SetMessage(Message);
		UVerticalBoxSlot* slot = Cast<UVerticalBoxSlot>(this->ContainerPanel->AddChild(Line));
		if (UFuncLib::CheckObject(slot, FSIG_APPEND(" Couldn't get HBox slot"))) {
			//slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Top);
			slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			slot->SetSize(ESlateSizeRule::Type::Automatic);
		}
	}
}

FString	UDebugWidget::GetAllContent() {
	FString Content;
	auto childrens = this->ContainerPanel->GetAllChildren();
	for (auto line : childrens) {
		UDebugLine* debugLine = Cast<UDebugLine>(line);
		if (debugLine) {
			Content.Append(debugLine->TextBox->GetText().ToString());
			Content.Append("\n");
		}
	}
	return Content;
}
