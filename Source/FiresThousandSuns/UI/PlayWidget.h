// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NamedValueSlider.h"
#include "Components/Button.h"
#include "../FiresThousandSunsPlayerState.h"

#include "PlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIRESTHOUSANDSUNS_API UPlayWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	FPlayerStats	GeneratePlayerStats() const;
	UFUNCTION(BlueprintCallable)
	void	InitSliders();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_MovSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_Life;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_LifeRegen;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_FireRes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_SpellSuppChance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_SpellSuppEffect;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_Fortify;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UNamedValueSlider*	NVSlider_LessDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UButton* EnterArenaButton;
protected:
	virtual void NativeConstruct() override;
};
