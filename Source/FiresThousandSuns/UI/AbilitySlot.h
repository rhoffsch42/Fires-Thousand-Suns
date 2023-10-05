// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/Image.h"
#include "../Abilitys/Ability.h"

#include "AbilitySlot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilitySlotClicked, class UAbilitySlot*, AbilitySlot);

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilitySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void	UpdateWidget();
	UFUNCTION(BlueprintCallable)
	void	LinkAbility(UAbility* Ability);
	UFUNCTION(BlueprintCallable)
	void	UnLinkAbility();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UButton*	Button;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	USlider*	CooldownSlider;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UImage*		Image;

	FAbilitySlotClicked	AbilitySlotClicked;
protected:
	virtual void NativeConstruct() override;
	virtual void Tick(FGeometry MyGeometry, float InDeltaTime);

	UAbility* _Ability = nullptr;
};
