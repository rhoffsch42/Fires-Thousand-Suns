// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "CommonTextBlock.h"

#include "NamedValueSlider.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UNamedValueSlider : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void	SetTitleAndRange(FText Text, float MinValue, float MaxValue);
	UFUNCTION(BlueprintCallable)
	double	SliderValueToRange(float Value) const;
	UFUNCTION(BlueprintCallable)
	void	SetSliderValue(float Value) const;
	UFUNCTION(BlueprintCallable)
	void	UpdateWithPercent(float Value) const;
	UFUNCTION(BlueprintCallable)
	double	GetValue() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	USlider* SliderWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock* TextTitle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock* TextValue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	Min = 0.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	Max = 100.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText	Unit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool	bDisplayAsInteger = true;
	bool	bDisplayUnit = true;
protected:
	virtual	void	NativeConstruct() override;
			void	_LinkSliderToFunc(USlider* Slider, const FName& FuncName);

};
