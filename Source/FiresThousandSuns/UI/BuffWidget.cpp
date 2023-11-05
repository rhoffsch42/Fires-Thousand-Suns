
#include "BuffWidget.h"
#include "../FuncLib.h"
#include "Misc/Timespan.h"

void	UBuffWidget::NativeConstruct() {
	Super::NativeConstruct();
	this->bHasScriptImplementedTick = false;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("UHealthWidget::NativeConstruct()"));
}

//void	UBuffWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
//	Super::NativeTick(MyGeometry, InDeltaTime);
//}

void	UBuffWidget::LinkBuff(UPARAM(ref) ABuff* Buff) {
	this->_LinkedBuff = Buff;
	this->Image->SetBrushFromMaterial(Buff->IconMaterial);
}

void	UBuffWidget::OnBuffExpired(ABuff* Buff) {
	// buff has already been linked so we dont really need the `Buff` parameter, it's only here to match the delegate parameters `FBuffExpired`
	this->_LinkedBuff = nullptr;
	this->RemoveFromParent();
	//if (this->GetParent()) {	}
}

ABuff* UBuffWidget::GetLinkedBuff() const { return this->_LinkedBuff; }

//////////////////////////////////////

void	UBuffWidgetValue::NativeConstruct() {
	Super::NativeConstruct();
	this->bHasScriptImplementedTick = true;
}

void	UBuffWidgetValue::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (this->_LinkedBuff) {
		this->Text->SetText(FText::FromString(this->_LinkedBuff->GetDisplayString()));
	}
}

//////////////////////////////////////

void	UBuffWidgetDuration::NativeConstruct() {
	Super::NativeConstruct();
	this->bHasScriptImplementedTick = true;
}

void	UBuffWidgetDuration::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (this->_LinkedBuff) {
		FTimespan time(0, 0, this->_LinkedBuff->GetLifeSpan());
		FString timestring(time.ToString(TEXT("%m:%s")));
		timestring.RemoveAt(0, 2);
		this->TextDuration->SetText(FText::FromString(timestring));
	}
}

//////////////////////////////////////

void	UBuffWidgetValueDuration::NativeConstruct() {
	Super::NativeConstruct();
	this->bHasScriptImplementedTick = true;
}

void	UBuffWidgetValueDuration::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (this->_LinkedBuff) {
		this->Text->SetText(FText::FromString(this->_LinkedBuff->GetDisplayString()));
		FTimespan time(0, 0, this->_LinkedBuff->GetLifeSpan());
		FString timestring(time.ToString(TEXT("%m:%s")));
		timestring.RemoveAt(0, 2);
		this->TextDuration->SetText(FText::FromString(timestring));
	}
}
