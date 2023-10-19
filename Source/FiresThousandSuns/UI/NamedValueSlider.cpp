
#include "NamedValueSlider.h"
#include "Internationalization/Text.h"

void	UNamedValueSlider::NativeConstruct() {
	Super::NativeConstruct();

	this->_LinkSliderToFunc(this->SliderWidget, "UpdateWithPercent");
	this->UpdateWithPercent(0.75);
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

void	UNamedValueSlider::UpdateWithValue(float Value) const {
	Value = std::max(std::min(this->Max, (double)Value), this->Min);
	this->TextValue->SetText(FText::Format(
		NSLOCTEXT("Fires", "key1", "{0}{1}"),
		FText::AsNumber(this->bDisplayAsInteger ? (int32)Value : Value),
		this->bDisplayUnit ? this->Unit : FText()
	));
	this->SliderWidget->SetValue(this->ValueToSliderPercent(Value));
}

void	UNamedValueSlider::UpdateWithPercent(float Percent) const {
	this->SliderWidget->SetValue(Percent);
	double v = this->SliderPercentToValue(Percent);
	this->TextValue->SetText(FText::Format(
		NSLOCTEXT("Fires", "key2", "{0}{1}"),
		FText::AsNumber(this->bDisplayAsInteger ? (int32)v : v),
		this->bDisplayUnit ? this->Unit : FText()
	));
	//FText::Format(NSLOCTEXT("Solus", "Solus", "HP "), FText::AsNumber(4));
	//FText::Format(NSLOCTEXT("Solus", "DayFmt", "{0} {1}"), NSLOCTEXT("Solus", "Solus", "Day"), FText::AsNumber(4)); // takes both as arguments
	//FText::Format(NSLOCTEXT("Solus", "Solus", "Day {0}"), FText::AsNumber(5)); // takes just the day number and formats it into the Day string
}

double	UNamedValueSlider::SliderPercentToValue(float Percent) const {
	return this->Min + Percent * (this->Max - this->Min);//this can overflow if user put min and max too far from each other
}

double	UNamedValueSlider::ValueToSliderPercent(float Value) const {
	return (Value - this->Min) / (this->Max - this->Min);
}

double	UNamedValueSlider::GetValue() const {
	return this->SliderPercentToValue(this->SliderWidget->GetValue());
}
