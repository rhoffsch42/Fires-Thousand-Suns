
#include "BuffWidget.h"
#include "../FuncLib.h"
#include "Misc/Timespan.h"

void	UBuffWidget::NativeConstruct() {
	Super::NativeConstruct();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("UHealthWidget::NativeConstruct()"));
}

void	UBuffWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
}

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

void	UBuffWidgetGuard::NativeConstruct() {
	Super::NativeConstruct();
	this->_FormatOptions.MaximumFractionalDigits = 0;
}

void	UBuffWidgetGuard::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (this->_BuffGuard) {
		this->TextValue->SetText(FText::AsNumber(this->_BuffGuard->HealthManager->GetHP(), &this->_FormatOptions));
		FTimespan time(0, 0, this->_BuffGuard->GetLifeSpan());
		FString timestring(time.ToString(TEXT("%m:%s")));
		timestring.RemoveAt(0, 2);
		this->TextDuration->SetText(FText::FromString(timestring));
	}
}

void	UBuffWidgetGuard::LinkBuff(UPARAM(ref) ABuff* Buff) {
	Super::LinkBuff(Buff);
	this->_BuffGuard = Cast<ABuffGuard>(Buff);
	UFuncLib::CheckObject(this->_BuffGuard, "UBuffWidgetGuard::LinkBuff() Cast<ABuffGuard>() failed");
}
