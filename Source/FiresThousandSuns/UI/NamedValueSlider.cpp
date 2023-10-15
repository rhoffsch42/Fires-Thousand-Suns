
#include "NamedValueSlider.h"
#include "Internationalization/Text.h"

void	UNamedValueSlider::NativeConstruct() {
	Super::NativeConstruct();

	this->_LinkSliderToFunc(this->SliderWidget, "UpdateWithPercent");
	this->SetSliderValue(0.75);
	this->TextTitle->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.5f, 0.14f, 1.0f)));
	this->TextValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.5f, 0.14f, 1.0f)));
}

void	UNamedValueSlider::_LinkSliderToFunc(USlider* Slider, const FName& FuncName) {
	Slider->OnValueChanged.Clear();
	FScriptDelegate script;
	script.BindUFunction(this, FuncName);
	Slider->OnValueChanged.Add(script);
}

void	UNamedValueSlider::SetTitleAndRange(FText Text, float MinValue, float MaxValue) {
	this->TextTitle->SetText(Text);
	this->Min = MinValue;
	this->Max = MaxValue;
	this->UpdateWithPercent(this->SliderWidget->GetValue());
}

double	UNamedValueSlider::SliderValueToRange(float Value) const {
	return this->Min + Value * (this->Max - this->Min);//this can overflow if user put min and max too far from each other
}

void	UNamedValueSlider::SetSliderValue(float Value) const {
	this->SliderWidget->SetValue(Value);
	this->UpdateWithPercent(this->SliderWidget->GetValue());
}

void	UNamedValueSlider::UpdateWithPercent(float Value) const {
	double v = this->SliderValueToRange(Value);
	this->TextValue->SetText(FText::Format(
		NSLOCTEXT("Fires", "key", "{0}{1}"),
		FText::AsNumber(this->bDisplayAsInteger ? (int32)v : v),
		this->bDisplayUnit ? this->Unit : FText()
	));
	//FText::Format(NSLOCTEXT("Solus", "Solus", "HP "), FText::AsNumber(4));
	//FText::Format(NSLOCTEXT("Solus", "DayFmt", "{0} {1}"), NSLOCTEXT("Solus", "Solus", "Day"), FText::AsNumber(4)); // takes both as arguments
	//FText::Format(NSLOCTEXT("Solus", "Solus", "Day {0}"), FText::AsNumber(5)); // takes just the day number and formats it into the Day string
}

double	UNamedValueSlider::GetValue() const {
	return this->SliderValueToRange(this->SliderWidget->GetValue());
}
