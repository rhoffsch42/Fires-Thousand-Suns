
#include "HealthWidget.h"


void	UHealthWidget::NativeConstruct() {
	Super::NativeConstruct();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("UHealthWidget::NativeConstruct()"));
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
		this->HpText->SetText(FText());
		this->MaxHpText->SetText(FText());
	}
}
