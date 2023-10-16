
#include "HealthWidget.h"

void	UHealthWidget::NativeConstruct() {
	Super::NativeConstruct();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("UHealthWidget::NativeConstruct()"));
}

void	UHealthWidget::Tick(FGeometry MyGeometry, float InDeltaTime) {
	Super::Tick(MyGeometry, InDeltaTime);
}

void	UHealthWidget::UpdateHP(double HP, double MaxHP) {
	//this->HpText->SetText(FText::Format(
	//	NSLOCTEXT("Fires", "key", "{0} / {1}"),
	//	FText::AsNumber(HP),
	//	FText::AsNumber(MaxHP)
	//));
	FNumberFormattingOptions options;
	options.MaximumFractionalDigits = 0;
	this->HealthBar->SetPercent(HP / MaxHP);
	if (this->_bDisplayText) {
		this->HpText->SetText(FText::AsNumber(HP, &options));
		this->MaxHpText->SetText(FText::AsNumber(MaxHP, &options));
	}
}

void	UHealthWidget::SetDisplayText(bool Display) {
	this->_bDisplayText = Display;
	if (!this->_bDisplayText) {
		this->HpText->SetVisibility(ESlateVisibility::Hidden);
		this->MaxHpText->SetVisibility(ESlateVisibility::Hidden);
		this->Separator->SetVisibility(ESlateVisibility::Hidden);
	} else {
		this->HpText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		this->MaxHpText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		this->Separator->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void	UHealthWidget::SetFontSize(float NewSize) const {
	FSlateFontInfo info = this->HpText->GetFont();
	info.Size = NewSize;
	this->HpText->SetFont(info);

	info = this->MaxHpText->GetFont();
	info.Size = NewSize;
	this->MaxHpText->SetFont(info);

	info = this->Separator->GetFont();
	info.Size = NewSize;
	this->Separator->SetFont(info);
}
