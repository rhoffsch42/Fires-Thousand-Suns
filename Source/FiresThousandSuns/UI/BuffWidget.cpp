
#include "BuffWidget.h"

void	UBuffWidget::NativeConstruct() {
	Super::NativeConstruct();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("UHealthWidget::NativeConstruct()"));
}

void	UBuffWidget::Tick(FGeometry MyGeometry, float InDeltaTime) {
	Super::Tick(MyGeometry, InDeltaTime);
	//if (!this->_LinkedBuff->IsValidLowLevel()) {
	//	this->OnBuffExpired(this->_LinkedBuff);
	//}
	GEngine->AddOnScreenDebugMessage((int32)(int64)this, 5.0f, FColor::Yellow, FString("Tick BuffWidget"));
}

void	UBuffWidget::LinkBuff(UPARAM(ref) ABuff* Buff) {
	this->_LinkedBuff = Buff;
	this->Image->SetBrushFromMaterial(Buff->IconMaterial);
}
void	UBuffWidget::OnBuffExpired(ABuff* Buff) {
	// buff has already been linked so we dont really need the `Buff` parameter, it's only here to match the delegate parameters `FBuffExpired`
	this->_LinkedBuff = nullptr;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("Buff Expired"));
	this->RemoveFromParent();
	//if (this->GetParent()) {	}
}

ABuff* UBuffWidget::GetLinkedBuff() const { return this->_LinkedBuff; }
